using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SnowController : MonoBehaviour
{
    private ParticleSystem system;
    private GameObject gc;
    private bool isEnabled;

    // Start is called before the first frame update
    void Start() 
    {
        gc = GameObject.Find("Snow");
        system = gc.GetComponent<ParticleSystem>();
        print(system);
        system.Stop();
        isEnabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        toogleOnorOff();
    }

    private void toogleOnorOff()
    {
        if (Input.GetKeyDown(KeyCode.M))
        {
            isEnabled = !isEnabled;
            system.Play();
            if (isEnabled)
                system.Play();
            else
                system.Stop();
        }
    }

}
