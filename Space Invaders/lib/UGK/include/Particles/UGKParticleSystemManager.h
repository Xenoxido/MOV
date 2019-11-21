/**
*	@file	 UGKParticleSystemManager.h
*	@author  Iván Sánchez Padilla & Rosa María Giménez Pérez
*	@date	 2016/07
*   @version 1.0
*
*	@brief	 Header of particle system manager class
**/

#include <UGKParticleSystem.h>

#ifndef CPARTICLESYSMAN_H
#define CPARTICLESYSMAN_H

using namespace std;
		
namespace UGK
{
	///Struct with system information 
	struct systeminfo {
		int t; ///< Starting time of the system
		int sysID; ///< System ID 
		int parID; ///< Particle ID

	};

	/**
	* @brief CParticleSystemManager \n
	* Represents the particle system manager
	*/
	class CParticleSystemManager
	{
		int particulas_creadas, particulas_emitidas, sistemas_creados, sistemas_emitidos; ///< number of created particles, number of emitted particles, number of created systems and number of emitted systems. Useful for debugging purposes
		bool mostrarResumen; ///< Indicates if the information of created and emitted particles and systems is going to be showed
		vector<systeminfo> systemsinfo; ///< Descriptions of systems to be used
		vector<CParticle*> part_pool; ///< Dead particles storage 
		vector<CParticleSystem*> sys_pool; ///< Dead systems storage
		vector<CParticleSystem*> active_sys; ///< Current active systems
		vector<sParticleSystem*> sys_descrip; ///< Systems descriptions  
		vector<sParticle*> part_descrip; ///< Particles descriptions
	private:
		void createSystem();
	public:
		CParticleSystemManager();
		void render();
		void update(int t);
		void init();
		void addInfo(systeminfo info);
		CParticle* getParticle();
		void recyclePart(CParticle *part);
	};
}
#endif