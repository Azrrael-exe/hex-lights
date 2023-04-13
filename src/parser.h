#ifndef parser_h
#define parser_h

#include <Arduino.h>

class Parser {
    private:
        uint8_t header;
        uint8_t buffer[5];
        bool ready;
    public:
        Parser(uint8_t header);
        bool isReady();
        void listen(Stream& uart);
        void getPayload(uint32_t& color, uint8_t& effect, uint8_t& timer);
};

Parser::Parser(uint8_t header) {
    this->header = header;
    this->ready = false;
}

bool Parser::isReady(){
    return this->ready;
}

void Parser::listen(Stream& uart) {
    if (this->header == uint8_t(uart.read())) {
        uint8_t input_buffer[6];
        uart.readBytes(input_buffer, 6);
        uint32_t sum = 0;
        for(int i=0; i < (6 -1); i++){
            sum += input_buffer[i];
        }
        if((0xFF - uint8_t(sum)) == input_buffer[5]){
            for(int i=0; i < 5; i++) {
                this->buffer[i] = input_buffer[i];
            }
            this->ready = true;
        }
    }
}

void Parser::getPayload(uint32_t& color, uint8_t& effect, uint8_t& timer) {
    this->ready = false;
    color = this->buffer[0];
    color = color << 8 | this->buffer[1];
    color = color << 8 | this->buffer[2];
    effect = this->buffer[3];
    timer = this->buffer[5];
}

#endif