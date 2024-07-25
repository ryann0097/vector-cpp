# Introduction


Nesta seção, apresentamos o conjunto principal de operações que um TAD Lista deve suportar, independentemente da estrutura de dados subjacente que se escolha para implementar uma lista.
A maioria das operações apresentadas aqui e nas próximas seções segue a convenção de nomenclatura e comportamento adotada pelos contêineres STL.

# Author(s) 

**Ryan David dos Santos Silvestre**
_ryan.silvestre.718@ufrn.edu.br_


# Problems found or limitations

**Limitações:**
Pequenos problemas com as funções SIZE e PUSH_BACK.


# Compiling and Runnig

A compilação pode ser feita da seguinte maneira:

g++ -Wall -std=c++11 -I source/include -I source/tm/ source/main.cpp source/tm/test_manager.cpp source/iterator_tests.cpp -o build/run_tests

Daí, você irá na pasta raiz do projeto e rodará com o seguinte comando:
$ ./build/run_tests.
