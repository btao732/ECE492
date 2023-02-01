----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/31/2023 06:46:51 PM
-- Design Name: 
-- Module Name: PISO_shift_register - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PISO_shift_register is
    generic ( size : integer := 7);
    Port ( data_in : in STD_LOGIC_VECTOR (size downto 0);
           clk : in STD_LOGIC;
           latch : in std_logic;
           rst : in STD_LOGIC;
           serial_out : out STD_LOGIC);
end PISO_shift_register;

architecture Behavioral of PISO_shift_register is    
signal data : std_logic_vector(size downto 0);
begin
    -- input register and clear
    process(clk)
    begin
        if (rising_edge(clk)) then
            if (rst = '1') then
                data <= (others => '0');
            elsif (latch = '1') then
                data <= data_in;
            else 
                serial_out <= data(0); -- output data
                data <= '0' & data(size downto 1); -- shift data
            end if;            
        end if;
    end process;
end Behavioral;
