    const uart_config_t uart_config = {
        .baud_rate = dev_config->baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .source_clk = clk_source,
    };

    uart_param_config(dev_config->channel, &uart_config);
    uart_set_pin(dev_config->channel, dev_config->tx_gpio_num, dev_config->rx_gpio_num, -1, -1);

    /* Install UART driver for interrupt-driven reads and writes */

    //运行中断有问题 可以修改这里
    ret = uart_driver_install(dev_config->channel, 256, 0, 0, NULL, ESP_INTR_FLAG_SHARED | ESP_INTR_FLAG_LOWMED);
    if (ret != ESP_OK) {
        goto _exit;
    }
