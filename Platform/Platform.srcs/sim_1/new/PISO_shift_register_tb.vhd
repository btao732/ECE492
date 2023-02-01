----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/31/2023 07:07:48 PM
-- Design Name: 
-- Module Name: PISO_shift_register_tb - Behavioral
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

entity PISO_shift_register_tb is
--  Port ( );
end PISO_shift_register_tb;

architecture Behavioral of PISO_shift_register_tb is
component PISO_shift_register is
    generic ( size : integer := 7);
    Port ( data_in : in STD_LOGIC_VECTOR (size downto 0);
           clk : in STD_LOGIC;
           latch : in std_logic;
           rst : in STD_LOGIC;
           serial_out : out STD_LOGIC);
end component;

constant clk_period : time := 50ns;

signal data_in_tb : std_logic_vector (7 downto 0);
signal clk_tb : std_logic := '0';
signal latch_tb : std_logic;
signal rst_tb : std_logic;
signal serial_out_tb : std_logic;

begin
    shift_register : PISO_shift_register port map (
                                    data_in => data_in_tb,
                                    clk => clk_tb,
                                    latch => latch_tb,
                                    rst => rst_tb,
                                    serial_out => serial_out_tb);

    -- Clock process
    process
    begin
    clk_tb <= not clk_tb;
    wait for clk_period;
    clk_tb <= not clk_tb;
    wait for clk_period;
    end process;
    
    -- testbench process
    process
    begin
        wait until falling_edge(clk_tb);
        rst_tb <= '1';
        wait until falling_edge(clk_tb);
        rst_tb <= '0';
        data_in_tb <= "11110000";
        latch_tb <= '1';
        wait until falling_edge(clk_tb);
        latch_tb <= '0';
        wait;
    end process;   
end Behavioral;
