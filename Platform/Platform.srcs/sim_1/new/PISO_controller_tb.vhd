----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/03/2023 02:34:58 PM
-- Design Name: 
-- Module Name: PISO_controller_tb - Behavioral
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

entity PISO_controller_tb is
--  Port ( );
end PISO_controller_tb;

architecture Behavioral of PISO_controller_tb is

component PISO_controller is
    Port ( clk_s : in STD_LOGIC;
           serial : out std_logic);
end component;

constant clock_period : time := 20ns;
signal clk_tb : std_logic := '1';
signal serial_data_tb : std_logic;

begin
    controller : PISO_controller port map (clk_s => clk_tb, serial => serial_data_tb);
    
    process
    begin
        clk_tb <= not clk_tb;
        wait for clock_period;
        clk_tb <= not clk_tb;
        wait for clock_period;
    end process;

end Behavioral;
