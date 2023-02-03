----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/03/2023 02:06:05 PM
-- Design Name: 
-- Module Name: PISO_controller - Behavioral
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

entity PISO_controller is
    Port ( clk_s : in STD_LOGIC;
           serial : out std_logic);
end PISO_controller;

architecture Behavioral of PISO_controller is

component clk_divider is
    Port ( clk_in : in STD_LOGIC;
           clk_out : out STD_LOGIC);
end component;

component PISO_shift_register is
    generic ( size : integer := 7);
    Port ( data_in : in STD_LOGIC_VECTOR (size downto 0);
           clk : in STD_LOGIC;
           latch : in std_logic;
           rst : in STD_LOGIC;
           serial_out : out STD_LOGIC);
end component;

signal divided_clk : std_logic;
signal data : std_logic_vector (7 downto 0) := "10101010";
signal latch_c : std_logic := '0';
signal rst_c : std_logic := '0';

begin
    clock_divider : clk_divider port map ( clk_in => clk_s, clk_out => divided_clk);
    piso : PISO_shift_register port map ( data_in => data, 
                                          clk => divided_clk, 
                                          latch => latch_c, 
                                          rst => rst_c, 
                                          serial_out => serial);
    
    process (divided_clk) 
    variable loading : std_logic := '0';
    variable sending : std_logic := '0';
    variable bits_sent : integer := 0;
    begin        
        if (rising_edge(divided_clk)) then
            if (loading = '0' and sending = '0') then
                latch_c <= '1';               
                loading := '1';
            elsif (loading = '1') then
                latch_c <= '0';
                loading := '0';
                sending := '1';
            elsif (bits_sent = 7) then
                bits_sent := 0;
                sending := '0';
            elsif (sending = '1') then
                bits_sent := bits_sent + 1;
            end if;
        end if;
    end process;              
end Behavioral;
