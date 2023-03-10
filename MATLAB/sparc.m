classdef sparc
    %SPARC Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Access = private)
        voltageMap
    end

    methods (Access = public, Static)
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
    end
    
    methods (Access = public)
        function obj = sparc
            obj.voltageMap = containers.Map('KeyType', 'single', 'ValueType', 'uint8');
            inputfile = fopen('voltages.txt', 'r');
            voltages = fscanf(inputfile, '%d %f\n', [2 Inf]);
            for i = 1:256
                item = voltages(:, i);
                obj.voltageMap(item(2)) = item(1);
            end
            disp('Initialized SPARC');
            fclose(inputfile);
        end

        function uploadChannelWaveform(obj, A, n, l)
            arguments (Input)
                obj sparc
                A (:,:) single
                n {mustBePositive}
                l {mustBePositive}
            end
            outputfile = fopen('waveform.bin','w');
            for i = 1:n
                for j = 1:l
                    r = obj.map_8_to_16(obj.encodeVoltage(A(i,j)));
                    fwrite(outputfile, r,'uint16',0,'b');
                end
            end 
            fclose(outputfile);
        end

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

