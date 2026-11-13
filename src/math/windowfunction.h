/**
 *  OSM
 *  Copyright (C) 2018  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef WINDOWFUNCTION_H
#define WINDOWFUNCTION_H

#ifndef OSM_STANDALONE_DSP
#include <QDebug>
#include <QVariant>
#include <map>
#endif
#include <math.h>
#include "container/array.h"

class WindowFunction
#ifndef OSM_STANDALONE_DSP
    : QObject
#endif
{
#ifndef OSM_STANDALONE_DSP
    Q_OBJECT
#endif

public:
    enum Type {Rectangular, Hann, Hamming, FlatTop, BlackmanHarris, HFT223D, Exponental};
#ifdef OSM_STANDALONE_DSP
    explicit WindowFunction(Type type);
    WindowFunction(const WindowFunction &) = delete;
    WindowFunction &operator=(const WindowFunction &) = delete;
#else
    Q_ENUM(Type)
    static const std::map<Type, QString> TypeMap;

    explicit WindowFunction(Type type, QObject *parent = nullptr);
    static QVariant getTypes();
    QString static name(Type type) noexcept;
#endif

    void setSize(unsigned int size);
    unsigned int size() const;

    //! return gain for point \b{i} in vector size \n{N}
    float pointGain(float i, unsigned int N) const;

    Type type() const;

    void setType(Type t);

    //! return gain of point k (corrcted with global wf gain data)
    const float &get(unsigned int k) const;

    float gain() const;
    float norm() const;

private:
    Type m_type;
    unsigned int m_size;
    Container::array<float> m_data;
    float m_gain;
    float m_norm;

    //! calculate data for current type
    void calculate();
};
#ifndef OSM_STANDALONE_DSP
QDebug operator<<(QDebug dbg, const WindowFunction::Type &t);
#endif
#endif // WINDOWFUNCTION_H
