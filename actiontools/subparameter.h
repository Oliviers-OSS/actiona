/*
	Actiona
	Copyright (C) 2005-2017 Jonathan Mercier-Ganady

	Actiona is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actiona is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#pragma once

#include "actiontools_global.h"

#include <QSharedData>
#include <QVariant>
#include <QScriptProgram>

namespace ActionTools
{
	class SubParameterData : public QSharedData
	{
	public:
		SubParameterData() : code(false)								{}
		SubParameterData(const SubParameterData &other)
			: QSharedData(other), code(other.code), value(other.value)	{}

		bool code;
		QString value;
		QScriptProgram program;
	};

	class ACTIONTOOLSSHARED_EXPORT SubParameter
	{
	public:
		SubParameter(bool code = {}, const QString &value = {}, const QScriptProgram &program = {})
			: d(new SubParameterData())
		{
			d->code = code;
			d->value = value;
			d->program = program;
		}
		SubParameter(const SubParameter &other) : d(other.d)			{}

		bool isCode() const												{ return d->code; }
		QString value() const											{ return d->value; }
		QScriptProgram program() const									{ return d->program; }

		void setValue(bool code, const QString &value)
		{
			d->code = code;
			d->value = value;

			if(code)
				d->program = {value};
		}

		bool operator == (const SubParameter &other) const				{ return (isCode() == other.isCode() && value() == other.value()); }
		bool operator != (const SubParameter &other) const				{ return (isCode() != other.isCode() || value() != other.value()); }

	private:
		QSharedDataPointer<SubParameterData> d;
	};

    ACTIONTOOLSSHARED_EXPORT QDataStream &operator << (QDataStream &s, const SubParameter &subParameter);
    ACTIONTOOLSSHARED_EXPORT QDataStream &operator >> (QDataStream &s, SubParameter &subParameter);
	ACTIONTOOLSSHARED_EXPORT QDebug &operator << (QDebug &dbg, const SubParameter &subParameter);
}

Q_DECLARE_METATYPE(ActionTools::SubParameter)

