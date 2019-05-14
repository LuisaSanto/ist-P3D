using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Dot_Truck : System.Object
{
    public WheelCollider leftWheel;
    public GameObject leftWheelMesh;
    public WheelCollider rightWheel;
    public GameObject rightWheelMesh;
    public bool motor;
    public bool steering;
    public bool reverseTurn;
}

public class Dot_Truck_Controller : MonoBehaviour
{

    public float maxMotorTorque;
    public float maxSteeringAngle;
    public List<Dot_Truck> truck_Infos;
    private Rigidbody rb;
    private GameObject gc;
    private GameObject aux;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        gc = GameObject.Find("GameController");
        
    }

    public void VisualizeWheel(Dot_Truck wheelPair)
    {
        Quaternion rot;
        Vector3 pos;
        wheelPair.leftWheel.GetWorldPose(out pos, out rot);
        wheelPair.leftWheelMesh.transform.position = pos;
        wheelPair.leftWheelMesh.transform.rotation = rot;
        wheelPair.rightWheel.GetWorldPose(out pos, out rot);
        wheelPair.rightWheelMesh.transform.position = pos;
        wheelPair.rightWheelMesh.transform.rotation = rot;

    }

    // Update is called once per frame
    void Update()
    {
        float motor = maxMotorTorque * Input.GetAxis("Vertical");
        float steering = maxSteeringAngle * Input.GetAxis("Horizontal");
        float brakeTorque = Mathf.Abs(Input.GetAxis("Jump"));

        if(brakeTorque > 0.01)
        {
            brakeTorque = maxMotorTorque;
            motor = 0;
            rb.drag = 1.5f;
        }
        else
        {
            brakeTorque = 0;
            rb.drag = 0;
        }


        foreach(Dot_Truck truck_Info in truck_Infos)
        {
            if(truck_Info.steering == true)
            {
                truck_Info.leftWheel.steerAngle = truck_Info.rightWheel.steerAngle = ((truck_Info.reverseTurn) ? 1 : 1) * steering;
            }

            if(truck_Info.motor == true)
            {
                truck_Info.leftWheel.motorTorque = motor;
                truck_Info.rightWheel.motorTorque = motor;
            }
            truck_Info.leftWheel.brakeTorque = brakeTorque;
            truck_Info.rightWheel.brakeTorque = brakeTorque;

            VisualizeWheel(truck_Info);
        }
    }


    IEnumerator RecoverVehicle()
    {
        yield return new WaitForSeconds(5.0f);
        transform.rotation = Quaternion.Euler(0, 180, 0);
        transform.position = new Vector3(transform.position.x, 2, transform.position.z);

        if(gc.GetComponent<GameController>().numCheckPoint == 0)
        {
            aux = GameObject.Find("Finish Line");
            transform.LookAt(aux.transform);
        }
        else if(gc.GetComponent<GameController>().numCheckPoint == 1)
        {
            aux = GameObject.Find("Checkpoint2");
            transform.LookAt(aux.transform);
        }
        else if (gc.GetComponent<GameController>().numCheckPoint == 2)
        {
            aux = GameObject.Find("Checkpoint3");
            transform.LookAt(aux.transform);
        }
        else if (gc.GetComponent<GameController>().numCheckPoint == 3)
        {
            aux = GameObject.Find("Checkpoint4");
            transform.LookAt(aux.transform);
        }
        else if (gc.GetComponent<GameController>().numCheckPoint == 4)
        {
            aux = GameObject.Find("Finish Line");
            transform.LookAt(aux.transform);
        }
    }

    private void OnTriggerEnter(Collider coll)
    {
        if(coll.tag == "Track")
        {
            StartCoroutine(RecoverVehicle());
        }
        if(coll.tag == "Walls")
        {
            gc.GetComponent<GameController>().numLifes -= 1;
            print(gc.GetComponent<GameController>().numLifes);
            
            if (gc.GetComponent<GameController>().numLifes == 0)
            {
                gc.GetComponent<GameController>().numLifes = 3;
                //transform.rotation = Quaternion.Euler(0, 180, 0);
                //transform.position = new Vector3(transform.position.x, 2, transform.position.z);
                if (gc.GetComponent<GameController>().numCheckPoint == 0)
                {
                    aux = GameObject.Find("Finish Line");
                }
                else if (gc.GetComponent<GameController>().numCheckPoint == 1)
                {
                    aux = GameObject.Find("Finish Line");
                }
                else if (gc.GetComponent<GameController>().numCheckPoint == 2)
                {
                    aux = GameObject.Find("Checkpoint2");
                }
                else if (gc.GetComponent<GameController>().numCheckPoint == 3)
                {
                    aux = GameObject.Find("Checkpoint3");
                }
                else if (gc.GetComponent<GameController>().numCheckPoint == 4)
                {
                    aux = GameObject.Find("Checkpoint4");
                }
                transform.rotation = aux.transform.rotation;
                transform.position = aux.transform.position;
            }
            new WaitForSeconds(5.0f);
        }
    }

}
