using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyMovements : MonoBehaviour
{
    public NavMeshAgent agent;
    public string objectName;
    private GameObject _object;
    public bool aux;
    private GameObject enemy;
    private GameObject gc;


    public Action ac = new Action();

    public enum Action
    {
        accelerate,
        brake,
        turnLeft,
        turnRight,
        lowSpeed,
        ultraLowSpeed
    }


    // Start is called before the first frame update
    void Start()
    {
        enemy = GameObject.Find("Enemy");
        agent = enemy.GetComponent<NavMeshAgent>();
        agent.enabled = true;

        if (aux)
        {
            _object = GameObject.Find(objectName);
        }

        gc = GameObject.Find("GameController");
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Enemy")
        {
            print("Ola\n");
            print(ac);
            switch (ac)
            {   
         
                case Action.accelerate:
                    if (aux)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.transform.LookAt(other.GetComponent<NavMeshAgent>().destination);
                        other.GetComponent<EnemyController>().maxMotorTorque = 700;
                        other.GetComponent<EnemyController>().MotorValue = 0.5f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }
                    else
                    {
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.5f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }

                case Action.brake:
                    if (aux && gc.GetComponent<GameController>().numLapOpponent <= 0)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.transform.LookAt(other.GetComponent<NavMeshAgent>().destination);
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.5f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 1;
                        break;
                    }
                    else if (aux && gc.GetComponent<GameController>().numLapOpponent > 0)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.transform.LookAt(other.GetComponent<NavMeshAgent>().destination);
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.5f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 2.0f;
                        break;
                    }
                    else
                    {
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }

                case Action.turnLeft:
                    if (aux)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 1;
                        other.GetComponent<EnemyController>().steeringValue = -1;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }
                    else
                    {
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 1;
                        other.GetComponent<EnemyController>().steeringValue = -1;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }

                case Action.turnRight:
                    if (aux)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 1;
                        other.GetComponent<EnemyController>().steeringValue = 1;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }
                    else
                    {
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 1;
                        other.GetComponent<EnemyController>().steeringValue = 1;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }

                case Action.lowSpeed:
                    if (aux)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.transform.LookAt(other.GetComponent<NavMeshAgent>().destination);
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.2f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }
                    else
                    {
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.2f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }

                case Action.ultraLowSpeed:
                    if (aux)
                    {
                        agent.SetDestination(_object.transform.position);
                        other.transform.LookAt(other.GetComponent<NavMeshAgent>().destination);
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.005f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }
                    else
                    {
                        other.GetComponent<EnemyController>().maxMotorTorque = 600;
                        other.GetComponent<EnemyController>().MotorValue = 0.005f;
                        other.GetComponent<EnemyController>().steeringValue = 0;
                        other.GetComponent<EnemyController>().breakValue = 0;
                        break;
                    }
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
