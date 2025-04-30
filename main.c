#include "header_server.h"
Mode mode;
unsigned char u[5];
unsigned char p[5];
unsigned char new_u[5];
unsigned char new_p[5];
unsigned char tran_data[8];
unsigned char rec_data[13];
unsigned char data[9];

void delay(unsigned short factor) {
    unsigned short i, j;

    for (i = 0; i < factor; i++) {
        for (j = 500; j--;);
    }
}

void init_config() {
    init_can();
    init_uart();
    /* Enabling peripheral interrupt */
    PEIE = 1;

    /* Enabling global interrupt */
    GIE = 1;

}

void main(void) {
    init_config();
    mode = recv;
    while (1) {

        switch (mode) {
            case recv:
                recv_data();
                break;

            case transmit:
                trans_data();
                mode = recv;
                break;
        }

    }
}

void recv_data() {
    unsigned char flag = can_receive();
    static int ind = 0;
    static int go = 0;
    int num = 0;
    if (flag == 1) {
        for (int i = 0; i < 8; i++) {
            data[i] = rec_data[i + 5];
        }
        data[8] = '\0';
        for (int i = 0; i < 4; i++) {
            u[i] = data[i];
        }
        for (int i = 4; i < 8; i++) {
            p[i - 4] = data[i];
        }
        u[4] = '\0';
        p[4] = '\0';
        puts("Recieved u_st from client :- ");
        puts(u);
        puts("\n");
        puts("Recieved p_id from client:- ");
        puts(p);
        puts("\n");
        if (ch == '\r')
            ind = 1;
        if (ind == 1) {
            static int j = 0;
            if (go == 0) {
                puts("Enter the required p_id :-");
                go = 1;
            }
            if (j < 4) {
                if (ch != '\r' && ch != '\0') {
                    new_p[j] = ch;
                    putch(ch);
                    ch = '\0';
                    j++;
                }
            }
            if (j == 4) {
                num = 0;
                for (int i = 0; i < 4; i++) {
                    if (new_p[i] == p[i])
                        num++;
                }
                if (num == 4) {
                    static int k = 0;
                    if (go == 1) {
                        puts("Enter the required u_st :-");
                        go = 2;
                    }
                    if (k < 4) {
                        if (ch != '\r' && ch != '\0') {
                            new_p[k] = ch;
                            putch(ch);
                            ch = '\0';
                            k++;
                        }
                    }
                    if (k == 4) {
                        ch = '\r';
                        j = 0;
                        k = 0;
                        new_u[4] = '\0';
                        mode = transmit;
                        go = 0;
                        flag = 0;
                    }
                } else {
                    puts("\r\np_id is not matching\n\r");
                    go = 0;
                    flag = 0;
                    ch = '\0';
                    j = 0;
                }

            }

        }
    }
}

void trans_data() {
    for (int i = 0; i < 4; i++) {
        data[i] = new_u[i];
    }
    for (int i = 4; i < 8; i++) {
        data[i] = new_p[i - 4];
    }
    can_transmit();
    delay(1000);
    puts("\r\nTransfer Successfull \r\n");
    mode = recv;
}

