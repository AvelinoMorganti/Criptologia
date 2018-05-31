/*
     Avelino Morganti Neto - 2018 (onetimepadchannel@gmail.com)
      
     ATENÇÃO - Este é um projeto acadêmico. Tenha sempre a sua chave privada salva em mais de um lugar (Paper Wallet, HD, Pen drive...)
     Caso o microcontrolador queime ou aconteça algum imprevisto, é impossível recuperar sua chave. Crie backups antes de cifrá-la com este programa.

     UTILIZE ESTE PROGRAMA APENAS PARA FINS ACADÊMICOS E PARA FINS DE TESTES. SUA CHAVE PRIVADA É DE SUA RESPONSABILIDADE. NÃO EXISTE NENHUMA GARANTIA PARA ESTE PROGRAMA. 
     USE POR SUA CONTA E RISCO.
     
     Este programa é um software livre: você pode redistribuí-lo e / ou modificar sob os termos da Licença Pública Geral GNU, conforme publicada pela 
     a Free Software Foundation, versão 3 da Licença, ou (a seu critério) qualquer versão posterior.

     Este programa é distribuído na esperança de que seja útil, mas SEM QUALQUER GARANTIA; sem mesmo a garantia implícita de COMERCIABILIDADE OU ADEQUAÇÃO A UM DETERMINADO FIM. Veja o
     GNU General Public License para mais detalhes.

     Você deveria ter recebido uma cópia da Licença Pública Geral GNU junto com este programa. Se não, veja <http://www.gnu.org/licenses/>
*/

#include <EEPROM.h>
#include "AESLib.h"

char *hex = NULL;
int lastAddress = 0;

//uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23}; //Chave do AES
uint8_t key[] = {73,109,112,111,115,116,111,32,101,32,114,111,117,98,111,46,32,83,111,110,101,103,117,101};
uint8_t iv[]  = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23}; //Vetor de Inicialização do CBC

char data[] = "Private key: 5JNoArCkTHzwUSRXsqmvM5DM9RmBjQ5XfVztHdbiPhNi4JEAWDc"; //64 chars == 64 bytes
int keySize = 64; //Precisa ser mod 16

void setup(){
    Serial.begin(9600);
    Serial.println("Original:");

    //cleanEEPROM();
    //showEEPROM();
    
    printData(); 

    //Cifração
    aes_context ctx = aes192_cbc_enc_start(key, iv);
    aes192_cbc_enc(key, iv, data, keySize);
    aes128_cbc_enc_continue(ctx, data, keySize); 
    aes192_cbc_enc_finish(ctx);

    Serial.println("Encrypted: ");
    printData();
      
    //keyWhitening();  //Elimina a chave da memória SRAM

    saveEEPROM();  //Salva a chave cifrada na EEPROM

    //Decifração
    ctx = aes192_cbc_dec_start(key, iv);
    aes192_cbc_dec(key, iv, data, keySize);
    aes192_cbc_dec_continue(ctx, data, keySize);
    aes192_cbc_dec_finish(ctx);

    Serial.println("Decrypted: ");
    printData();
     
    showEEPROM(0, 70);  //Mostra os dados do byte 0 até o 70º byte
}

void loop(){}

//Limpa todos os dados da EEPROM
void cleanEEPROM(){
    for (int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
    }
    Serial.println("Clean!");  
}

//Salva a chave privada na EEPROM
void saveEEPROM(){
    for(int i = 0; i < 64; i++){
        //EEPROM.write(i, '0');
        EEPROM.write(i, data[i]);
    }
    lastAddress += 1;
    Serial.println("Saved!\n");    
}

void showEEPROM(int b, int e){
    byte value;
    char EEPROM_DATA[e];
    for(int i = b; i < e; i++){ 
        value = EEPROM.read(i);
        if(value == NULL){
            value = ' ';
        }
        EEPROM_DATA[i] = value;
        //Serial.print(value, HEX);
    }
    StringToHex(EEPROM_DATA, strlen((const char *)EEPROM_DATA), &hex);
    Serial.println(hex);
    hex = NULL;
}

void showKey(){
    for(int i =0;i<24;i++){
      Serial.print(data[i], DEC);
      Serial.print("");
      //char a = (char) (key[i]);
      //Serial.print(a);
    }
    Serial.println("");  
}

void keyWhitening(){
    for(int i = 0; i < 64; i++){
        if(i < 24){
            key[i] = 0;
            iv[i] = 0;      
        }
        data[i] = 0;
    }
}

void printData(){
    Serial.println(data);
    /*
    for(int i = 0; i < 64; i++){
        byte c = char (data[i]);
        Serial.print(c, HEX);
    }
    */
    StringToHex(data, strlen((const char *)data), &hex);
    Serial.println(hex);
    hex = NULL;
    Serial.println("");    
}

void StringToHex(char *szInput, size_t size_szInput, char **lpszOut){
    char *pin = szInput;
    const char *hex = "0123456789ABCDEF";
    size_t outSize = size_szInput * 2 + 2;
    *lpszOut = new char[outSize];
    char *pout = *lpszOut;
    for (; pin < szInput + size_szInput; pout += 2, pin++)
    {
        pout[0] = hex[(*pin >> 4) & 0xF];
        pout[1] = hex[*pin & 0xF];
    }
    pout[0] = 0;
}









