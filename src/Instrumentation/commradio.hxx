// commradio.hxx -- class to manage a comm radio instance
//
// Written by Adrian Musceac, started August 2011.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


#ifndef __cplusplus
# error This library requires C++
#endif

#include <simgear/compiler.h>
#include <simgear/structure/subsystem_mgr.hxx>

#include <Main/fg_props.hxx>

#include <simgear/math/sg_geodesy.hxx>
#include <simgear/debug/logstream.hxx>
#include <string>


using std::string;


class FGCommRadio : public SGSubsystem, public SGPropertyChangeListener
{
private:
	bool isOperable() const
		{ return _operable; }
	bool _operable; ///< is the unit serviceable, on, powered, etc
	
	double _receiver_sensitivity;
	double _transmitter_power;
	double _antenna_gain;
	
	int _propagation_model; /// 0 none, 1 round Earth, 2 ITM
	double ITM_calculate_attenuation(SGGeod tx_pos, double freq, int ground_to_air)
	
public:

    FGCommRadio(SGPropertyNode *node);
    ~FGCommRadio();

    void init ();
    void bind ();
    void unbind ();
    void update (double dt);
    
    void setFrequency(double freq, int radio);
    double getFrequency(int radio);
    void setTxPower(double txpower) { _transmitter_power = txpower; };
    // transmission_type: 1 for ground to air, 2 for air to air, 3 for pilot to ground, 4 for pilot to air
    void receive_text(SGGeod tx_pos, double freq, string text, int transmission_type);
    void setPropagationModel(int model) { _propagation_model = model; };
    
};

