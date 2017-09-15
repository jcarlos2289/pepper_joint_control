#include <signal.h>
#include <ros/ros.h>
#include <string>
//#include "MotionControllerFactory.h"
#include <naoqi_bridge_msgs/JointAnglesWithSpeed.h>
#include <math.h>
#include <boost/thread/thread.hpp>
//#include "MoveGenerator.h"
//#include "PepperJoint.h"

//Controlador de movimiento
//var::MotionController *controller;
//var::MoveGenerator *mvGen;

//Handler de cierre de ejecución
void mySigintHandler(int sig)
{
	//Parar el robot
	//controller->stop();
	//Parar el nodo
	ros::shutdown();
}

//Main para recibir ordenes de movimiento y transmitirlas
int main(int argc, char **argv)
{
	//Tipo de controlador
	std::string type;

	//var::PepperJoint pepJoint = var::PepperJoint.R_HAND;
	//Arrancar nodo
	ros::init(argc, argv, "motion_controller", ros::init_options::NoSigintHandler); //, ros::init_options::NoSigintHandler
	ros::NodeHandle nh;

	std::string jointVector[2] = {"RHand", "LHand"};
	int anglesVector[2] = {1.0, 0.0};

	std::cout << "Preparando envio." << std::endl;

	ros::Publisher move_pub = nh.advertise<naoqi_bridge_msgs::JointAnglesWithSpeed>("/joint_angles", 100);
	naoqi_bridge_msgs::JointAnglesWithSpeed msg;
	//Limpiar nombres y ángulos
	msg.joint_names.clear();
	msg.joint_angles.clear();
	msg.joint_names.push_back("LWristYaw");
	msg.joint_names.push_back("RWristYaw");
	msg.joint_angles.push_back(50 * M_PI / 180.0);
	msg.joint_angles.push_back(50 * M_PI / 180.0);
	msg.speed = 5.0;
	msg.relative = true;

	std::cout << "Empezando envio de mensaje" << std::endl;
	move_pub.publish(msg);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	std::cout << "Mensaje enviado." << std::endl;
	//Obtener parámetros
	ros::NodeHandle private_node_handle("~");

	//Tipo de controlador
	private_node_handle.param<std::string>("type", type, "");

	//Informar de los valores de las variables
	//std::cout<<"Controller type: "<<type<<std::endl;

	//Generar controlador
	//var::MotionControllerFactory factory;
	//controller = factory.generate(type, nh);
	//mvGen = new var::MoveGenerator(nh);
	//mvGen->moveJoint(pepJoint, 1.0,10,0.5,true);

	//Comprobar si se ha generado
	/*if(controller == NULL)
	{
	   std::cerr<<"Error. El tipo de controlador "<<type<<" no existe"<<std::cerr;
	   return -1;
	}*/

	//Definir handler de señal de cierre
	//	signal(SIGINT, mySigintHandler);

	//Crear retardo
	ros::Rate rate(10);

	//Bucle de ejecución
	while (ros::ok())
	{
		//Lanzar callbacks
		ros::spinOnce();
		//Realizar acciones
		//controller->execute();
		//Espera del bucle
		//rate.sleep();
	}
}
