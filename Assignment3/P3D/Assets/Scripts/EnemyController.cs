using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[System.Serializable]
public class EnemyScript : System.Object
{
    public WheelCollider leftWheel;
    public GameObject leftWheelMesh;
    public WheelCollider rightWheel;
    public GameObject rightWeelMesh;
    public bool motor;
    public bool steering;
    public bool reverseTurn;
}

public class EnemyController : MonoBehaviour
{
    public float maxMotorTorque;
    public float maxSteeringAngle;
    public List<Dot_Truck> truck_Infos;
    private Rigidbody rb;

    public float MotorValue;
    public float steeringValue;
    public float breakValue;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
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
        float motor = maxMotorTorque * MotorValue;
        float steering = maxSteeringAngle * steeringValue;
        float brakeTorque = Mathf.Abs(breakValue);

        if (brakeTorque > 0.001)
        {
            brakeTorque = maxMotorTorque;
            motor = 0;
            rb.drag = 2.0f;
        } else
        {
            brakeTorque = 0;
            rb.drag = 0;
        }

        foreach (Dot_Truck truck_Info in truck_Infos)
        {
            if (truck_Info.steering == true)
            {
                truck_Info.leftWheel.steerAngle = truck_Info.rightWheel.steerAngle = ((truck_Info.reverseTurn) ? 1 : 1) * steering;
            }

            if (truck_Info.motor == true)
            {
                truck_Info.leftWheel.motorTorque = motor;
                truck_Info.rightWheel.motorTorque = motor;
            }
            truck_Info.leftWheel.brakeTorque = brakeTorque;
            truck_Info.rightWheel.brakeTorque = brakeTorque;

            VisualizeWheel(truck_Info);
        }
    }


}
