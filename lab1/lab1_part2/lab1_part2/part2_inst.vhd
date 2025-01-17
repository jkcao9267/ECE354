	component part2 is
		port (
			sys_sdram_pll_0_ref_reset_reset          : in    std_logic                     := 'X';             -- reset
			sys_sdram_pll_0_ref_clk_clk              : in    std_logic                     := 'X';             -- clk
			new_sdram_controller_0_wire_addr         : out   std_logic_vector(12 downto 0);                    -- addr
			new_sdram_controller_0_wire_ba           : out   std_logic_vector(1 downto 0);                     -- ba
			new_sdram_controller_0_wire_cas_n        : out   std_logic;                                        -- cas_n
			new_sdram_controller_0_wire_cke          : out   std_logic;                                        -- cke
			new_sdram_controller_0_wire_cs_n         : out   std_logic;                                        -- cs_n
			new_sdram_controller_0_wire_dq           : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			new_sdram_controller_0_wire_dqm          : out   std_logic_vector(1 downto 0);                     -- dqm
			new_sdram_controller_0_wire_ras_n        : out   std_logic;                                        -- ras_n
			new_sdram_controller_0_wire_we_n         : out   std_logic;                                        -- we_n
			led_pio_external_connection_export       : out   std_logic_vector(7 downto 0);                     -- export
			seven_seg_pio_external_connection_export : out   std_logic_vector(13 downto 0);                    -- export
			button_pio_external_connection_export    : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			sys_sdram_pll_0_sdram_clk_clk            : out   std_logic                                         -- clk
		);
	end component part2;

	u0 : component part2
		port map (
			sys_sdram_pll_0_ref_reset_reset          => CONNECTED_TO_sys_sdram_pll_0_ref_reset_reset,          --         sys_sdram_pll_0_ref_reset.reset
			sys_sdram_pll_0_ref_clk_clk              => CONNECTED_TO_sys_sdram_pll_0_ref_clk_clk,              --           sys_sdram_pll_0_ref_clk.clk
			new_sdram_controller_0_wire_addr         => CONNECTED_TO_new_sdram_controller_0_wire_addr,         --       new_sdram_controller_0_wire.addr
			new_sdram_controller_0_wire_ba           => CONNECTED_TO_new_sdram_controller_0_wire_ba,           --                                  .ba
			new_sdram_controller_0_wire_cas_n        => CONNECTED_TO_new_sdram_controller_0_wire_cas_n,        --                                  .cas_n
			new_sdram_controller_0_wire_cke          => CONNECTED_TO_new_sdram_controller_0_wire_cke,          --                                  .cke
			new_sdram_controller_0_wire_cs_n         => CONNECTED_TO_new_sdram_controller_0_wire_cs_n,         --                                  .cs_n
			new_sdram_controller_0_wire_dq           => CONNECTED_TO_new_sdram_controller_0_wire_dq,           --                                  .dq
			new_sdram_controller_0_wire_dqm          => CONNECTED_TO_new_sdram_controller_0_wire_dqm,          --                                  .dqm
			new_sdram_controller_0_wire_ras_n        => CONNECTED_TO_new_sdram_controller_0_wire_ras_n,        --                                  .ras_n
			new_sdram_controller_0_wire_we_n         => CONNECTED_TO_new_sdram_controller_0_wire_we_n,         --                                  .we_n
			led_pio_external_connection_export       => CONNECTED_TO_led_pio_external_connection_export,       --       led_pio_external_connection.export
			seven_seg_pio_external_connection_export => CONNECTED_TO_seven_seg_pio_external_connection_export, -- seven_seg_pio_external_connection.export
			button_pio_external_connection_export    => CONNECTED_TO_button_pio_external_connection_export,    --    button_pio_external_connection.export
			sys_sdram_pll_0_sdram_clk_clk            => CONNECTED_TO_sys_sdram_pll_0_sdram_clk_clk             --         sys_sdram_pll_0_sdram_clk.clk
		);

