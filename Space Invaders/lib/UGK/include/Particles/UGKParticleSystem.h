/**
*	@file	 UGKParticleSystem.h
*	@author  Iván Sánchez Padilla & Rosa María Giménez Pérez
*	@date	 2016/07
*   @version 1.0
*
*	@brief	 Header of particle system class
**/
#include <vector>
#include <iostream>
#include <UGKParticle.h>


#ifndef CPARTICLESYS_H
#define CPARTICLESYS_H

using namespace std;

namespace UGK
{
	class CParticleSystemManager;

	///Struct with attributes needed to describe a particle system
	struct sParticleSystem {
		vector<float> pos;
		vector<float> vel;
		vector<float> ac;
		int t, life;
		int emission_freq, n_part_emitted; // particulas por segundo
		sParticle *part_desc;
		int dispersion_angle;
		int n_dispersion;
	};

	/**
	* @brief CParticleSystem \n
	* Represents a particle system. Inherits from CCharacter class
	*/
	class CParticleSystem : public CCharacter {
	public:
		// Speed, Position y Acceleration heredados
		bool alive, partAlive; ///< Indicates is system is alive and if any of its particles is also alive
		int t_prev, life, n_part_emit, t_part_prev; ///< time of last update, remaining life, number of emited particles and time of last emitted particle
		int emission_freq, n_part_emitted; ///< emissions per second and number of particles per emission
		sParticle *part_desc; ///< description of particle used in the system
		int dispersion_angle; ///< dispersion angle of particle emission
		int n_dispersion; ///< number of subdivisions in the dispersion
		vector<vector<float>> part_vel; ///< Velocity vector for each subdivision direction 
		vector<CParticle*> active_part; ///< Active particles in the system
		CParticleSystemManager *manager; ///< Pointer to system manager
		
		CParticleSystem(CParticleSystemManager *man);
		CParticleSystem() {};
		void init(sParticleSystem *data);
		void render();
		void update(int t);
		bool isAlive();
		bool particlesAlive();
	private:
		void updatePos(int elapsed);
		void updateLife(int elapsed);
		void updateVel(int elapsed);
		void emitParticle();
	};
}
#endif