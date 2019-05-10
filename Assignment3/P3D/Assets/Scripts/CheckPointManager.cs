using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckPointManager : MonoBehaviour {

    private GameObject gc;
    public bool playerWins;
    public bool opponentWins;

    public enum CheckPoints
    {
        one,
        two,
        three,
        four,
    };

    public CheckPoints cp = new CheckPoints();

    void Start ()
    {
        gc = GameObject.Find("GameController");
        gc.GetComponent<GameController>().playerLapStarted = false;
        gc.GetComponent<GameController>().numCheckPoint = 0;
        gc.GetComponent<GameController>().numLapPlayer = 0;
        gc.GetComponent<GameController>().bestTimeOpponent = 1000;
        gc.GetComponent<GameController>().bestTimePlayer = 1000;

    }
	
	void Update ()
    {
		
	}

    void OnTriggerEnter(Collider coll)
    {
        if (coll.tag == "Player")
        {
            if (cp == CheckPoints.one && gc.GetComponent<GameController>().numCheckPoint == 0 && gc.GetComponent<GameController>().numLapPlayer == 0)
            {
                gc.GetComponent<GameController>().playerLapStarted = true;
                gc.GetComponent<GameController>().numCheckPoint = 1;
            }


            else if (cp == CheckPoints.two && gc.GetComponent<GameController>().numCheckPoint == 1)
            {
                gc.GetComponent<GameController>().numCheckPoint = 2;
            }

            else if (cp == CheckPoints.three && gc.GetComponent<GameController>().numCheckPoint == 2)
            {
                gc.GetComponent<GameController>().numCheckPoint = 3;
            }

            else if (cp == CheckPoints.four && gc.GetComponent<GameController>().numCheckPoint == 3)
            {
                gc.GetComponent<GameController>().numCheckPoint = 4;
            }

            if (cp == CheckPoints.one && gc.GetComponent<GameController>().numCheckPoint == 4)
            {
                gc.GetComponent<GameController>().numLapPlayer++;
                gc.GetComponent<GameController>().playerLapStarted = false;
                gc.GetComponent<GameController>().lastTimePlayer = gc.GetComponent<GameController>().playerTime;

                if (gc.GetComponent<GameController>().lastTimePlayer < gc.GetComponent<GameController>().bestTimePlayer)
                {
                    gc.GetComponent<GameController>().bestTimePlayer = gc.GetComponent<GameController>().lastTimePlayer;
                }

                gc.GetComponent<GameController>().playerTime = 0;
                gc.GetComponent<GameController>().playerLapStarted = true;
                gc.GetComponent<GameController>().numCheckPoint = 1;
            }

            if (cp == CheckPoints.one && gc.GetComponent<GameController>().numCheckPoint == 1 && gc.GetComponent<GameController>().numLapPlayer == 3)
            {
                gc.GetComponent<GameController>().playerWins = true;
            }
        }


        if (coll.tag == "Opponent")
        {
            if (cp == CheckPoints.one && gc.GetComponent<GameController>().numCheckPointOpponent == 0
            && gc.GetComponent<GameController>().numLapOpponent == 0)
            {
                gc.GetComponent<GameController>().opponentLapStarted = true;
                gc.GetComponent<GameController>().numCheckPointOpponent = 1;
            }


            else if (cp == CheckPoints.two && gc.GetComponent<GameController>().numCheckPointOpponent == 1)
            {
                gc.GetComponent<GameController>().numCheckPointOpponent = 2;
            }

            else if (cp == CheckPoints.three && gc.GetComponent<GameController>().numCheckPointOpponent == 2)
            {
                gc.GetComponent<GameController>().numCheckPointOpponent = 3;
            }

            else if (cp == CheckPoints.four && gc.GetComponent<GameController>().numCheckPointOpponent == 3)
            {
                gc.GetComponent<GameController>().numCheckPointOpponent = 4;
            }

            if (cp == CheckPoints.one && gc.GetComponent<GameController>().numCheckPointOpponent == 4)
            {
                gc.GetComponent<GameController>().numLapOpponent++;
                gc.GetComponent<GameController>().opponentLapStarted = false;
                gc.GetComponent<GameController>().lastTimeOpponent = gc.GetComponent<GameController>().opponentTime;

                if (gc.GetComponent<GameController>().lastTimeOpponent < gc.GetComponent<GameController>().bestTimeOpponent)
                {
                    gc.GetComponent<GameController>().bestTimeOpponent = gc.GetComponent<GameController>().lastTimeOpponent;
                }

                gc.GetComponent<GameController>().opponentTime = 0;
                gc.GetComponent<GameController>().opponentLapStarted = true;
                gc.GetComponent<GameController>().numCheckPointOpponent = 1;
            }


            if (cp == CheckPoints.one && gc.GetComponent<GameController>().numCheckPointOpponent == 1
            && gc.GetComponent<GameController>().numLapOpponent == 3)
            {
                gc.GetComponent<GameController>().opponentWins = true;
            }

        }


    }

}
