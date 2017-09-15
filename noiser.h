#ifndef NOISER_H
#define NOISER_H

#include "cachedFastNoiseObject.h"
#include "hash.h"
#include <node.h>
#include <random>
#include <unordered_map>

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Exception;

class Noiser : public node::ObjectWrap {
  public:
    static Persistent<Function> constructor;
    static void Init(Isolate* isolate);
    static void NewInstance(const FunctionCallbackInfo<Value>& args);

    std::mt19937 rng;
    FastNoiseObject elevationNoise1;
    FastNoiseObject elevationNoise2;
    FastNoiseObject elevationNoise3;
    CachedFastNoiseObject wormNoise;
    CachedFastNoiseObject oceanNoise;
    CachedFastNoiseObject riverNoise;
    CachedFastNoiseObject temperatureNoise;
    CachedFastNoiseObject humidityNoise;

    std::unordered_map<std::pair<int, int>, unsigned char> biomeCache;
    std::unordered_map<std::tuple<unsigned char, int, int>, float> biomeHeightCache;
    std::unordered_map<std::pair<int, int>, float> elevationCache;

    explicit Noiser(int seed);

    static void New(const FunctionCallbackInfo<Value>& args);
    static void GetBiome(const FunctionCallbackInfo<Value>& args);
    unsigned char getBiome(int x, int z);
    static void GetBiomeHeight(const FunctionCallbackInfo<Value>& args);
    float getBiomeHeight(unsigned char b, int x, int z);
    static void GetElevation(const FunctionCallbackInfo<Value>& args);
    float getElevation(int x, int z);
    static void GetTemperature(const FunctionCallbackInfo<Value>& args);
    double getTemperature(double x, double z);
    static void FillBiomes(const FunctionCallbackInfo<Value>& args);
    void fillBiomes(int ox, int oz, unsigned char *biomes);
    static void FillElevations(const FunctionCallbackInfo<Value>& args);
    void fillElevations(int ox, int oz, float *elevations);
    static void FillEther(const FunctionCallbackInfo<Value>& args);
    void fillEther(float *elevations, float *ether);
};

#endif