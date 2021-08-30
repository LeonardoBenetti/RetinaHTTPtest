# RetinaHTTPtest
Este repositório contém alguns programas que utilizei para testar as requisições HTTP do retina

## Versões utilizadas
- Python: 3.9.6
- Flask: 1.1.2
- Werkzeug: 0.16.0
- pipenv: version 2021.5.29
- cmake: version 3.16.3

## Configurando ambiente virtual para o servidor
Eu segui algo parecido com as informações desse site: http://digitalocean.com/community/tutorials/processing-incoming-request-data-in-flask-pt

Depois de clonar o repositório, na pasta `./RetinaServer` crie um ambiente virtual com Flask:
  
  ```sh
  pipenv install Flask
  ```
  
E abra o ambiente virtual com:
  
  ```sh
  pipenv shell
  ```
  
Para ativar o servidor utilize dentro desse ambiente virtual o comando:
```sh
 python app.py
 ```

Para o teste da sendHTTP é importante configurar no arquivo `.RetinaServer/app.py` a variável `UPLOAD_FOLDER` com o caminho completo de onde você deseja que o arquivo seja salvo no seu computador.

## Compilando o o código c++
No diretório `./testLibCurl/build` execute os seguintes comandos:

```sh
cmake ../
```

```sh
cmake --build .
```

Para rodar o teste, ainda no diretório `./testLibCurl/build`, execute:

```sh
./tstlibcurl X
```

Onde X pode ser 1, 2 ou 3 dependendo do teste que se deseja fazer.
