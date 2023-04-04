classdef sparc
    % Class for initializing and controlling SPARC arrays.

    properties (Access = private)
        % Lookup Table for converting float voltages to 
        % an 8 bit representation.
        voltageMap
    end

    methods (Access = public, Static)
        % Function developed by Randy Palamar to generate
        % appropriate 16 bit value from the 8 bit value,
        % dependant on hardware architecture.
        function r = map_8_to_16(b)
            arguments (Input)
                b uint8 {mustBeNumeric}
            end
            arguments (Output)
                r uint16
            end
            r = 0;
            for i = 0:7     
                if (bitand(b, bitshift(1, i)))
                    r = bitor(r, bitshift(1, 2 * i));
                else
                    r = bitor(r, bitshift(1, 2 * i + 1));
                end
            end
        end

        % Function to generate calibration voltages for
        % all input combinations
        function createCalibrationVoltages(voltageIn)
            if nargin < 1
                voltageIn = 250.0;
            end
            outputfile = fopen('voltages.txt', 'w');
            for i = 0:2^8-1
                fprintf(outputfile, "%d %f\n", i, i * voltageIn / (2^8));
            end
            fclose(outputfile);
        end
        
        % Helper function to send waveform binary 
        % over first available serial port
        function sendWaveform()
            freeports = serialportlist("available");
            if isempty(freeports)
                disp("No serial port found");
                return
            end
            device = serialport(freeports(1), 115200);
            inputfile = fopen("waveform.bin");
            [data, size] = fread(inputfile, [1 Inf], 'uint8');
            for i = 1:size
                write(device, data(i), 'uint8');
            end
            fclose(inputfile);
            delete(device);
        end
    end
    
    methods (Access = public)
        % Constructor uses file "voltages.txt" to 
        % generate voltageMap lookup table.
        function obj = sparc(maxVoltage)
            obj.voltageMap = containers.Map('KeyType', 'single', 'ValueType', 'uint8');
            if nargin < 1
                maxVoltage = 250;
            end
            sparc.createCalibrationVoltages(maxVoltage);
            inputfile = fopen('voltages.txt', 'r');
            voltages = fscanf(inputfile, '%d %f\n', [2 Inf]);
            for i = 1:256
                item = voltages(:, i);
                obj.voltageMap(item(2)) = item(1);
            end
            disp('Initialized SPARC');
            fclose(inputfile);
        end
        
        % Upload voltage waveform for n channels to SPARC 
        % system, takes an n*l matrix of floats.
        function generateChannelWaveform(obj, A)
            arguments (Input)
                obj sparc
                A (:,:) single
            end
            [n, l] = size(A);
            outputfile = fopen('waveform.bin','w');
            fwrite(outputfile, n, "uint32", 0, 'b'); % Write number of channels first
            fwrite(outputfile, l, "uint32", 0, 'b'); % Write samples per channel second
            for i = 1:n
                for j = 1:l
                    r = obj.map_8_to_16(obj.encodeVoltage(A(i,j)));
                    fwrite(outputfile, r,'uint16',0,'b');
                end
            end
            fclose(outputfile);
        end
            
        % Function takes float and converts to 8-bit 
        % representation that is closest to the 
        % desired voltage.
        function val = encodeVoltage(obj, desiredVoltage)
            arguments (Input)
                obj sparc
                desiredVoltage single
            end
            arguments (Output)
                val uint8
            end
            delta = 300.0;
            for k = keys(obj.voltageMap)
                newDelta = desiredVoltage - k{1};
                if (abs(newDelta) < abs(delta))
                    delta = newDelta;
                    closestVoltage = k{1};
                end
            end
            val = obj.voltageMap(closestVoltage);
        end
    end
end