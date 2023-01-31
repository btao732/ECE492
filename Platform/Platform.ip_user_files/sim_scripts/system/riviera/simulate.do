onbreak {quit -force}
onerror {quit -force}

asim +access +r +m+system -L xilinx_vip -L axi_infrastructure_v1_1_0 -L axi_vip_v1_1_12 -L processing_system7_vip_v1_0_14 -L xil_defaultlib -L lib_cdc_v1_0_2 -L proc_sys_reset_v5_0_13 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.system xil_defaultlib.glbl

set NumericStdNoWarnings 1
set StdArithNoWarnings 1

do {wave.do}

view wave
view structure

do {system.udo}

run -all

endsim

quit -force
