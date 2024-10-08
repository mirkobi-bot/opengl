#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

/**
    Classe di supporto per gestire le informazion di luce ambientale
*/
class AmbientLight {
    glm::vec3 _color; ///<< Colore della luce
    float _intensity; ///<< Intensità della luce

public:
    /**
        Setta la luce al colore bianco e massima intensità
    */
    AmbientLight();
    /**
        Setta la luce al colore e intensità dati
        @param col colore dela luce
        @param i intensità della luce
    */
    AmbientLight(const glm::vec3 &col, float i);

    /**
        Incrementa l'intensità della luce della quantità data
        @param value valore di incremento
    */
    void inc(float value);

    /**
        Decrementa l'intensità della luce della quantità data
        @param value valore di decremento
    */
    void dec(float value);

    /**
        Ritorna il colore della luce
    */
    glm::vec3 color() const;

    /**
        Ritorna l'intensità della luce
    */
    float intensity() const;
};

class DirectionalLight {
    glm::vec3 _color; ///<< Colore della luce
    glm::vec3 _direction; ///<< Direzione della sorgente
public:
    /**
        Setta la luce al colore bianco.
        La direzione di default è un vettore verticale verso il basso.
    */
    DirectionalLight();

    /**
        Setta la luce al colore e intensità dati
        @param col colore dela luce
        @param i intensità della luce
    */

    DirectionalLight(const glm::vec3 &col, const glm::vec3 &dir);

    /**
        Ritorna il colore della luce
    */
    glm::vec3 color() const;

    /**
        Ritorna la direzione della luce
    */
    glm::vec3 direction() const;

};

class DiffusiveLight {
    float _intensity; /// Intensità della luce

public:
    /**
        Setta la luce al colore bianco e massima intensità e posizionata in alto
        La direzione di irraggiamento di default è un vettore verticale verso il basso.
    */
    DiffusiveLight();

    /**
        Setta la luce al colore e intensità dati
        @param col colore dela luce
        @param i intensità della luce
    */
    DiffusiveLight(float i);

    /**
        Incrementa l'intensità della luce della quantità data
        @param value valore di incremento
    */
    void inc(float value);

    /**
        Decrementa l'intensità della luce della quantità data
        @param value valore di decremento
    */
    void dec(float value);

    /**
        Ritorna l'intensità della luce
    */
    float intensity() const;
};


class SpecularLight {
  float     _shininess; ///<< esponente di shininess
  float     _intensity; ///<< Intensità della luce

public:

  /**
    Setta la luce alla massima intensità. La posizione della camera è quella di 
    default. La shininess è settata a 30.
  */
  SpecularLight();

  /**
    Setta la luce speculare 
    @param col colore dela luce
    @param i intensità della luce
  */
  SpecularLight(float i,float s);

  /**
    Incrementa l'intensità della luce della quantità data
    @param value valore di incremento
  */
  void inc(float value);

  /**
    Decrementa l'intensità della luce della quantità data
    @param value valore di decremento
  */
  void dec(float value);

  /**
    Incrementa l'intensità della luce della quantità data
    @param value valore di incremento
  */
  void inc_shine(float value);

  /**
    Decrementa l'intensità della luce della quantità data
      @param value valore di decremento
  */
  void dec_shine(float value);

  /**
      Ritorna l'intensità della luce
  */
  float intensity() const;

  /**
      Ritorna il valore di shininess
  */
  float shininess() const;

};

class PointLight {
    glm::vec3 _color; ///<< Colore della luce
    glm::vec3 _position; ///<< Posizione della sorgente
    float _constant; ///<< Fattore di attenuazione costante
    float _linear; ///<< Fattore di attenuazione lineare
    float _quadratic; ///<< Fattore di attenuazione quadratica
public:
    PointLight();
    PointLight(const glm::vec3 &col, const glm::vec3 &pos, float constant, float linear, float quadratic);
    glm::vec3 color() const;
    glm::vec3 position() const;
    float constant() const;
    float linear() const;
    float quadratic() const;
    void incX(float value);
    void decX(float value);
    void incY(float value);
    void decY(float value);
    void incZ(float value);
    void decZ(float value);
};

class SpotLight {
    glm::vec3 _color; ///<< Colore della luce
    glm::vec3 _position; ///<< Posizione della sorgente
    glm::vec3 _direction; ///<< Direzione della luce
    float _cutOff; ///<< Angolo di taglio
    float _outerCutOff; ///<< Angolo di taglio esterno
    float _constant; ///<< Fattore di attenuazione costante
    float _linear; ///<< Fattore di attenuazione lineare
    float _quadratic; ///<< Fattore di attenuazione quadratica
public:
    SpotLight();
    SpotLight(const glm::vec3 &col, const glm::vec3 &pos, const glm::vec3 &dir, float cutOff, float outerCutOff, float constant, float linear, float quadratic);
    glm::vec3 color() const;
    glm::vec3 position() const;
    glm::vec3 direction() const;
    float cutOff() const;
    float outerCutOff() const;
    float constant() const;
    float linear() const;
    float quadratic() const;
};

#endif