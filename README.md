# Criptologia - Projetos
Repositório dos projetos do canal Criptologia no Youtube: https://www.youtube.com/criptologia

Apoie: 1CriPTo6QLCLHe6qjzz4dVjUAQm9EnZHQu

Criptologia Hardware Wallet
==============

Hardware Wallet PARA PROPÓSITOS ACADÊMICOS

```c
/*
ATENÇÃO - Este é um projeto acadêmico. Tenha sempre a sua chave privada salva em mais de um lugar (Paper Wallet, HD, Pen drive...). caso o microcontrolador queime ou aconteça algum imprevisto, é impossível recuperar sua chave. Crie backups antes de cifrá-la com este programa.

UTILIZE ESTE PROGRAMA APENAS PARA FINS ACADÊMICOS E PARA FINS DE TESTES. SUA CHAVE PRIVADA É DE SUA RESPONSABILIDADE. NÃO EXISTE NENHUMA GARANTIA PARA ESTE PROGRAMA. USE POR SUA CONTA E RISCO.
*/
```

Este projeto utiliza a biblioteca [AESLib](https://github.com/DavyLandman/AESLib). Os fontes foram colocados no mesmo diretóri do sketch do Arduino para facilitar o teste por usuários novatos.

Instalação
-----
*Em edição*

Uso
-----
Digitar a chave privada a ser cifrada em data[]. Ter atenção que são necessários 64 caracteres (ou quantidade de caracteres mod 16)

```c
char data[] = "Private key: 5JNoArCkTHzwUSRXsqmvM5DM9RmBjQ5XfVztHdbiPhNi4JEAWDc"; //64 chars == 64 bytes
```

Recursos
-----

-  [X] Armazenamento seguro com AES 192 em CBC
-  [ ] Receber pagamentos (identificar)
-  [ ] Geração de números verdadeiramente aleatórios
-  [ ] Geração de chave (curva elíptica)
-  [ ] Assinatura de transações Bitcoin
-  [ ] Interface gráfica
-  [ ] Conexão com Internet
-  [ ] Proteção contra fault-injection
-  [ ] Execução em tempo constante
-  [ ] Proteção contra ataques de side channel conhecidos

Exemplo de uso do AES em CBC

```c
    //Cifração
    aes_context ctx = aes192_cbc_enc_start(key, iv);
    aes192_cbc_enc(key, iv, data, keySize);
    aes128_cbc_enc_continue(ctx, data, keySize); 
    aes192_cbc_enc_finish(ctx);
    
     //Decifração
    ctx = aes192_cbc_dec_start(key, iv);
    aes192_cbc_dec(key, iv, data, keySize);
    aes192_cbc_dec_continue(ctx, data, keySize);
    aes192_cbc_dec_finish(ctx);
```

Funções:
	
```c
void cleanEEPROM();
void saveEEPROM();
void showEEPROM(int b, int e);
void showKey(); //Unicamente para testes
void keyWhitening();
void printData();
void StringToHex(char *szInput, size_t size_szInput, char **lpszOut);
```
