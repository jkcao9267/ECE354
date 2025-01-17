`timescale 100 ps/10 ps

// The `timescale directive specifies that
// the simulation time unit is 100 ps and
// the simulator timestep is 10 ps

module rle_testbench;
	// signal declaration
	reg clkt, rstt;
	reg recv_readyt, send_readyt;
	reg [7:0] in_datat;
	reg end_of_streamt;
	wire [23:0] out_datat;
	wire rd_reqt, wr_reqt;

	// instantiate the circuit under test
	rle_enc uut
		(.clk(clkt), .rst(rstt), .recv_ready(recv_readyt), .send_ready(send_readyt), .in_data(in_datat), .end_of_stream(end_of_streamt), .out_data(out_datat), .rd_req(rd_reqt), .wr_req(wr_reqt));


	// clock running forever
	initial
	begin
	clkt=1'b0;
	end

	always
	begin
	#1 clkt=~clkt;
	// Clock signal assignment
	end

	// reset for a few cycles
	initial
	begin
	recv_readyt = 1'b1;
	send_readyt = 1'b1;
	end_of_streamt = 1'b0;
	#1 rstt=1'b1;
	#2 rstt=1'b0;
	// Reset signal assignment
	end

	// test vector generator
	initial
	begin
	//test vector 1
	#1 in_datat[7:0]= 8'b00000000;
	//test vector 2
	#42 in_datat[7:0]=8'b11111111;
	//test vector 3
	#46 in_datat[7:0]=8'b01010101; //worse case
	//test vector 4
        #109 in_datat[7:0]=8'b11111110;
	//test vector 5
	#49 in_datat[7:0]=8'b10000000;
	//test vector 6
	#57 in_datat[7:0]=8'b00001111;
	//test vector 7
	#48 in_datat[7:0]=8'b01111110;
	//test vector 8
	#58 in_datat[7:0]=8'b11001100;
	//test vector 9
	#61 in_datat[7:0]=8'b11101111;
	//test vector 10
	#61 in_datat[7:0]=8'b11110101;
	//test series with all 0
	#82 in_datat[7:0]=8'b00000000;
	#42 in_datat[7:0]=8'b00000000;
	#42 in_datat[7:0]=8'b00000000;
	#42 in_datat[7:0]=8'b00000000;
	$stop;
	end
endmodule
