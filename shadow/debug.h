#ifndef DEBUG_H
#define DEBUG_H

#include "shaderclass.h"
#include "light.h"

/**
    Classe che include le funzionalità specifiche legate agli shader da usare
    nell'applicazione.
    Sono stati overloadati i metodi load_shaders e load_done.
    Sono stati inseriti due metodi pubblici per settare la matrice di trasformazione
    delle coordinate dei vertici.
*/
class Debug : public ShaderClass
{
public:
    void set_depthmap(int unit);

private:
    /**
        Metodo per il caricamento degli shader

        @return true se il caricamento è andato a buon fine
    */
    virtual bool load_shaders();

    /**
        Metodo che recupera tutte le location delle variabili uniform
        negli shader caricati.

        @return se le operazioni post-load sono andate a buon fine
    */
    virtual bool load_done();
    GLint _depthmap_location;
};
#endif