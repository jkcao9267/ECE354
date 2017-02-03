
module part2 (
	sys_sdram_pll_0_ref_reset_reset,
	sys_sdram_pll_0_ref_clk_clk,
	new_sdram_controller_0_wire_addr,
	new_sdram_controller_0_wire_ba,
	new_sdram_controller_0_wire_cas_n,
	new_sdram_controller_0_wire_cke,
	new_sdram_controller_0_wire_cs_n,
	new_sdram_controller_0_wire_dq,
	new_sdram_controller_0_wire_dqm,
	new_sdram_controller_0_wire_ras_n,
	new_sdram_controller_0_wire_we_n,
	led_pio_external_connection_export,
	seven_seg_pio_external_connection_export,
	button_pio_external_connection_export,
	sys_sdram_pll_0_sdram_clk_clk);	

	input		sys_sdram_pll_0_ref_reset_reset;
	input		sys_sdram_pll_0_ref_clk_clk;
	output	[12:0]	new_sdram_controller_0_wire_addr;
	output	[1:0]	new_sdram_controller_0_wire_ba;
	output		new_sdram_controller_0_wire_cas_n;
	output		new_sdram_controller_0_wire_cke;
	output		new_sdram_controller_0_wire_cs_n;
	inout	[15:0]	new_sdram_controller_0_wire_dq;
	output	[1:0]	new_sdram_controller_0_wire_dqm;
	output		new_sdram_controller_0_wire_ras_n;
	output		new_sdram_controller_0_wire_we_n;
	output	[7:0]	led_pio_external_connection_export;
	output	[13:0]	seven_seg_pio_external_connection_export;
	input	[3:0]	button_pio_external_connection_export;
	output		sys_sdram_pll_0_sdram_clk_clk;
endmodule
