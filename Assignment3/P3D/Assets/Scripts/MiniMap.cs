using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MiniMap : MonoBehaviour
{ 
    public GameObject playerIcon;
    public GameObject enemyIcon;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void Awake()
    {
        playerIcon.layer = LayerMask.NameToLayer("MiniMap");
        enemyIcon.layer = LayerMask.NameToLayer("MiniMap");

    }

}
