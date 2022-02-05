#pragma once

#include <Arduino.h>
#include <cmath>
#include <cstring>

template <typename T> T inline linlin(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x <= in_min)
        return out_min;
    if (x >= in_max)
        return out_max;
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <typename T> T inline explin(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x <= in_min)
        return out_min;
    if (x >= in_max)
        return out_max;
    return (log(x / in_min)) / (log(in_max / in_min)) * (out_max - out_min) + out_min;
}

template <typename T> T inline expexp(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x <= in_min)
        return out_min;
    if (x >= in_max)
        return out_max;
    return pow(out_max / out_min, log(x / in_min) / log(in_max / in_min)) * out_min;
}

template <typename T> T inline linexp(T x, T in_min, T in_max, T out_min, T out_max) {
    if (x <= in_min)
        return out_min;
    if (x >= in_max)
        return out_max;
    return pow(out_max / out_min, (x - in_min) / (in_max - in_min)) * out_min;
}

template <typename T> T inline lincurve(T x, T in_min, T in_max, T out_min, T out_max, int curve = -4, const char* clip="minmax") {
	T grow, a, b, scaled;
	if(strcmp(clip, "minmax") == 0) {
		if(x <= in_min)
            return out_min;
		if(x >= in_max) 
            return out_max;
    } else if(strcmp(clip, "min") == 0) {
		if(x <= in_min) 
            return out_min;
    } else if(strcmp(clip, "max") == 0) {
		if(x >= in_max) 
            return out_max;
    }
	if(abs(curve) < 0.001) {
		return (x - in_min) / (in_max - in_min) * (out_max - out_min) + out_min;
	}
	grow = exp(curve);
	a = out_max - out_min / (1.0 - grow);
	b = out_min + a;
	scaled = (x - in_min) / (in_max - in_min);
	return b - (a * pow(grow, scaled));
}

template <typename T> T inline curvelin(T x, T in_min, T in_max, T out_min, T out_max, int curve = -4, const char* clip="minmax") {
	T grow, a, b, scaled;
	if(strcmp(clip, "minmax") == 0) {
		if(x <= in_min)
            return out_min;
		if(x >= in_max) 
            return out_max;
    } else if(strcmp(clip, "min") == 0) {
		if(x <= in_min) 
            return out_min;
    } else if(strcmp(clip, "max") == 0) {
		if(x >= in_max) 
            return out_max;
    }
	if(abs(curve) < 0.001) {
		return (x - in_min) / (in_max - in_min) * (out_max - out_min) + out_min;
	}
	grow = exp(curve);
	a = in_max - in_min / (1.0 - grow);
	b = in_min + a;
	return log((b - x) / a) * (out_max - out_min) / curve + out_min;
}

template <typename T> T inline bilin(T x, T in_center, T in_min, T in_max, T out_center, T out_min, T out_max, const char* clip="minmax") {
	if(strcmp(clip, "minmax") == 0) {
		if(x <= in_min)
            return out_min;
		if(x >= in_max) 
            return out_max;
    } else if(strcmp(clip, "min") == 0) {
		if(x <= in_min) 
            return out_min;
    } else if(strcmp(clip, "max") == 0) {
		if(x >= in_max) 
            return out_max;
    }
	if(x >= in_center) {
		return linlin(x, in_center, in_max, out_center, out_max, "none");
	} else {
		return linlin(x, in_min, in_center, out_min, out_center, "none");
	}
}

template <typename T> T inline biexp(T x, T in_center, T in_min, T in_max, T out_center, T out_min, T out_max, const char* clip="minmax") {
	if(strcmp(clip, "minmax") == 0) {
		if(x <= in_min)
            return out_min;
		if(x >= in_max) 
            return out_max;
    } else if(strcmp(clip, "min") == 0) {
		if(x <= in_min) 
            return out_min;
    } else if(strcmp(clip, "max") == 0) {
		if(x >= in_max) 
            return out_max;
    }
	if(x >= in_center) {
		return explin(x, in_center, in_max, out_center, out_max, "none");
	} else {
		return explin(x, in_min, in_center, out_min, out_center, "none");
	}
}

//http://www.flipcode.com/archives/Fast_log_Function.shtml
/* inline float fast_log2 (float val) */
/* { */
/*    float f = val; */
/*    unsigned x; */
/*    std::memcpy(&x, &val, sizeof(f)); */
/*    const int log_2 = int((x >> 23) & 255) - 128; */
/*    x &= ~(unsigned(255u) << 23u); */
/*    x += unsigned(127) << 23u; */
/*    std::memcpy(&val, &x, sizeof(f)); */
/*    //1+log2(m), m ranging from 1 to 2 */
/*    //3rd degree polynomial keeping first derivate continuity. */
/*    //For less precision the line can be commented out */
/*    val = ((-1.f/3.f) * val + 2.f) * val - (2.f/3.f); */
/*    return val + static_cast<float>(log_2); */
/* } */

//randomness

template <typename T> T inline sum3rand(T min, T max) {
    return random(min, max) + random(min, max) + random(min, max);
}

