#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include <array>
#include <math.h>


template <typename T>
using is_arith = std::enable_if<std::is_arithmetic<T>::value && std::is_default_constructible<T>::value, void>;

template <typename T, typename... Ts>
using are_same = std::enable_if<(std::is_same<Ts, T>::value && ...), void>;

namespace GeomRel {

template<typename T, int N, typename = is_arith<T>>
class GRVector
{
public:
    T dot(const GRVector& other) const {
        T ret = _components[0] * other._components[0];
        for (int i = 1; i < N; ++i) {
            ret += _components[i] * other._components[i];
        }

        return ret;
    };

    GRVector normalized() const {
        GRVector vec(_components);

        vec.normalize();

        return vec;
    };

    T length() const {
        return std::sqrt(this->lengthSqr());
    }

    T lengthSqr() const {
        return this->dot(*this);
    }

    GRVector& normalize() {
        (*this) /= this->length();

        return *this;
    }

    GRVector& operator/=(T val) {
        for (auto& c : _components) {
            c /= val;
        }

        return *this;
    };

    GRVector operator+(const GRVector& other) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] += other._components[i];
        }

        return vec;
    };

    GRVector operator-(const GRVector& other) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] -= other._components[i];
        }

        return vec;
    };

    GRVector operator*(const GRVector& other) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] *= other._components[i];
        }

        return vec;
    };

    GRVector operator/(const GRVector& other) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] /= other._components[i];
        }

        return vec;
    };

    GRVector operator+(T val) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] += val;
        }

        return vec;
    };

    friend const GRVector operator+(T val, const GRVector& other) {
        GRVector vec(other._components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] += val;
        }

        return vec;
    };

    GRVector operator-(T val) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] -= val;
        }

        return vec;
    };

    GRVector operator*(T val) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] *= val;
        }

        return vec;
    };

    friend const GRVector operator*(T val, const GRVector& other) {
        GRVector vec(other._components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] *= val;
        }

        return vec;
    };

    GRVector operator/(T val) const {
        GRVector vec(_components);

        for (int i = 0; i < N; ++i) {
            vec._components[i] /= val;
        }

        return vec;
    };

    bool operator==(const GRVector& other) const {
        bool equal = true;
        for (int i = 0; i < N; ++i) {
            equal &= _components[i] == other._components[i];
        }

        return equal;
    }

    bool operator!=(const GRVector& other) const {
        return !(*this == other);
    }

    T x() const {
        if constexpr (N >= 1) {
            return _components[0];
        }
        return 0;
    }

    T y() const {
        if constexpr (N >= 2) {
            return _components[1];
        }
        return 0;
    }

    T z() const {
        if constexpr (N >= 3) {
            return _components[2];
        }
        return 0;
    }

    std::array<T, N> components() const { return _components; }

    template<typename... Ts, typename = are_same<T, Ts...>>
    GRVector(Ts... args) : _components{args...}
    {
        static_assert (sizeof...(Ts) <= N, "Instantiated Vector with wrong number of components");
    }

    explicit GRVector() {}

protected:
    GRVector(std::array<T, N> components) : _components(components) {};

private:
    std::array<T, N> _components;
};

using GRVector3 = GRVector<double, 3>;
using GRVector2 = GRVector<double, 2>;

}
