
module traffic_light_nios (
    // Тактовый сигнал частотой 50 МГц
    input  logic       clk_50,

    // Сигнал сброса: 0 — сброс, 1 — нормальная работа
    input  logic       reset_n,

    // Восемь входных переключателей
    input  logic [7:0] switches,

    // Восемь выходных сигналов для светодиодов
    output logic [7:0] leds
);

    // Подключаем процессорную систему, созданную в Qsys.
    // Внутри неё находятся Nios II, память, JTAG UART и PIO.
    nios_system u_nios_system (
        .clk_clk         (clk_50),
        .reset_reset_n   (reset_n),
        .leds_export     (leds),
        .switches_export (switches)
    );

endmodule
