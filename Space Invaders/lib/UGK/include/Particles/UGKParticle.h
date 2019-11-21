/**
*	@file	 UGKParticle.h
*	@author  Iván Sánchez Padilla & Rosa María Giménez Pérez
*	@date	 2016/07
*   @version 1.0
*
*	@brief	 Header of particle class
**/

#include <vector>
#include <iostream>
#include <UGKCharacter.h>

#ifndef CPARTICLES_H
#define CPARTICLES_H

using namespace std;

typedef enum {
	UGKP_UPD_PERIOD,
	UGKP_RND_PERIOD,
	UGKP_MAX_TIMERS
} CPL_EXTRA_TIMERS;
namespace UGK
{
	
	///Struct with description to fade from one color to another one
	struct sColorFades {
		vector<float> fadecolor, colorinc;
		int colorfade_ini, colorfade_dur;
	};

	///Struct with attributes needed to describe a particle
	struct sParticle {
		int life, t, fadeout_t;
		vector<float> pos;
		vector<float> vel;
		vector<float> ac;
		vector<float> color, fadecolor;
		int colorfade_ini, colorfade_dur;
		vector<float> scale, fadescale;
		int scalefade_ini, scalefade_dur;
		float angle;
		vector<float> rotAxis;
		float spin, spin_ac;
		vector<sColorFades> colorfadesinfo;
	};

	
	/**
	* @brief CParticle \n
	* Represents a particle. Inherits from CCharacter class
	*/
	class CParticle : public CCharacter {
		bool alive;	///< Indicates if particle is still alive
		vector<sColorFades> colorfadesinfo; ///< Vector with information about color transitions  
		vector<float> color, fadecolor, colorinc; ///< Initial and final color and step per ms
		vector<float> scale, fadescale, scaleinc; ///< Initial and final scale and step per ms
		int colorfade_ini, colorfade_dur; ///< Remaining life at which color fade starts and duration
		int scalefade_ini, scalefade_dur; ///< Remaining life at which scale fade starts and duration
		float angle; ///< Angle for rotation matrix
		vector<float> rotAxis; ///< Vector with rotation axis
		float spin, spin_ac; ///< spin from particle and its acceleration
		int t_prev, life, fadeout_t; ///< Time of last render, remaining life of particle and remaining life at which fade out starts
		
	public:
		float		Alpha,			///< For waving the vanishment of the bonus while falling downwards to the player
					FadingSpeed;	///< Velocity of Fading in and out the alpha channel of the texture for the bonus
		int			counteri;

		void render();
		void update(int t);
		void init(sParticle *data);
		bool isAlive();
		void setSpeed(float x, float y, float z);
		void setPos(float x, float y, float z);
	private:
		void updatePos(int elapsed);
		void updateAngle(int elapsed);
		void updateFade();
		void updateColor(int elapsed);
		void updateLife(int elapsed);
		void updateVel(int elapsed);
		void updateScale(int elapsed);
		void updateSpin(int elapsed);
			
	};
}
#endif