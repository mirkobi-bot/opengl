#include "light.h"

AmbientLight::AmbientLight() :
	_color(glm::vec3(1.0,1.0,1.0)), _intensity(1.0) {}

AmbientLight::AmbientLight(const glm::vec3 &col, float i) :
	_color(col), _intensity(i) {}

void AmbientLight::inc(float value) {
	_intensity += value;
	if (_intensity>1.0) _intensity = 1.0;
}

void AmbientLight::dec(float value) {
	_intensity -= value;
	if (_intensity < 0.0) _intensity = 0.0;
}

glm::vec3 AmbientLight::color() const {
	return _color;
}

float AmbientLight::intensity() const {
	return _intensity;
}

DirectionalLight::DirectionalLight() : 
  _color(glm::vec3(1.0f,1.0f,1.0f)), 
  _direction(glm::vec3(0.0f,-1.0f,0.0f))
{}

DirectionalLight::DirectionalLight(const glm::vec3 &col, const glm::vec3 &dir) :
  _color(col),
  _direction(dir) {} 

glm::vec3 DirectionalLight::color() const {
  return _color;
}

glm::vec3 DirectionalLight::direction() const {
  return _direction;
}

DiffusiveLight::DiffusiveLight() :
	_intensity(1.0f) {}

DiffusiveLight::DiffusiveLight(float i) :
	_intensity(i) {}

void DiffusiveLight::inc(float value) {
	_intensity += value;
	if (_intensity>1.0) _intensity = 1.0;
}

void DiffusiveLight::dec(float value) {
	_intensity -= value;
	if (_intensity < 0.0) _intensity = 0.0;
}


float DiffusiveLight::intensity() const {
	return _intensity;
}


SpecularLight::SpecularLight() :
  _shininess(30.0f),
  _intensity(1.0f) {}

SpecularLight::SpecularLight(float i, float s) :
    _intensity(i), _shininess(s) {}

void SpecularLight::inc(float value) {
  _intensity += value;
    if (_intensity>1.0) _intensity = 1.0;
}

void SpecularLight::dec(float value) {
  _intensity -= value;
  if (_intensity < 0.0) _intensity = 0.0;
}

void SpecularLight::inc_shine(float value) {
  _shininess += value;
}

void SpecularLight::dec_shine(float value) {
  _shininess -= value;
  if (_shininess < 0.0) _shininess = 0.0;
}

float SpecularLight::intensity() const {
  return _intensity;
}

float SpecularLight::shininess() const {
  return _shininess;
}

//gestione di point light e spot light

PointLight::PointLight() :
    _color(glm::vec3(1.0f, 1.0f, 1.0f)),
    _position(glm::vec3(0.0f, 0.0f, 0.0f)),
    _constant(1.0f),
    _linear(0.09f),
    _quadratic(0.032f)
{}

PointLight::PointLight(const glm::vec3 &col, const glm::vec3 &pos, float constant, float linear, float quadratic) :
    _color(col),
    _position(pos),
    _constant(constant),
    _linear(linear),
    _quadratic(quadratic)
{}

glm::vec3 PointLight::color() const {
    return _color;
}

glm::vec3 PointLight::position() const {
    return _position;
}

float PointLight::constant() const {
    return _constant;
}

float PointLight::linear() const {
    return _linear;
}

float PointLight::quadratic() const {
    return _quadratic;
}

/*
traslazione della luce puntuale
*/
void PointLight::incX(float value) {
  _position.x += value;
}

void PointLight::decX(float value) {
  _position.x -= value;
}

void PointLight::incY(float value) {
  _position.y += value;
}

void PointLight::decY(float value) {
  _position.y -= value;
}

void PointLight::incZ(float value) {
  _position.z += value;
}

void PointLight::decZ(float value) {
  _position.z -= value;
}




SpotLight::SpotLight() :
    _color(glm::vec3(1.0f, 1.0f, 1.0f)),
    _position(glm::vec3(0.0f, 0.0f, 0.0f)),
    _direction(glm::vec3(0.0f, -1.0f, 0.0f)),
    _cutOff(glm::cos(glm::radians(12.5f))),
    _outerCutOff(glm::cos(glm::radians(15.0f))),
    _constant(1.0f),
    _linear(0.09f),
    _quadratic(0.032f)
{}

SpotLight::SpotLight(const glm::vec3 &col, const glm::vec3 &pos, const glm::vec3 &dir, float cutOff, float outerCutOff, float constant, float linear, float quadratic) :
    _color(col),
    _position(pos),
    _direction(dir),
    _cutOff(glm::cos(glm::radians(cutOff))),
    _outerCutOff(glm::cos(glm::radians(outerCutOff))),
    _constant(constant),
    _linear(linear),
    _quadratic(quadratic)
{}

glm::vec3 SpotLight::color() const {
    return _color;
}

glm::vec3 SpotLight::position() const {
    return _position;
}

glm::vec3 SpotLight::direction() const {
    return _direction;
}

float SpotLight::cutOff() const {
    return _cutOff;
}

float SpotLight::outerCutOff() const {
    return _outerCutOff;
}

float SpotLight::constant() const {
    return _constant;
}

float SpotLight::linear() const {
    return _linear;
}

float SpotLight::quadratic() const {
    return _quadratic;
}