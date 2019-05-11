using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameController : MonoBehaviour
{
    //Player
    public int numCheckPoint;
    public int numLapPlayer;
    public int lapsLimit;

    public bool playerLapStarted;
    public bool playerWins;

    public float playerTime;
    public float lastTimePlayer;
    public float bestTimePlayer;

    //Opponent
    public int numCheckPointOpponent;
    public int numLapOpponent;

    public bool opponentLapStarted;
    public bool opponentWins;

    public float opponentTime;
    public float lastTimeOpponent;
    public float bestTimeOpponent;

    // Start is called before the first frame update
    void Start()
    {
        Time.timeScale = 1;

        numLapPlayer = 0;
        playerTime = 0.0f;
        playerWins = false;

        numLapOpponent = 0;
        opponentTime = 0.0f;
        opponentWins = false;
        
    }

    //Count player's time
    public void PlayerLapsCounter()
    {
        if (playerLapStarted)
        {
            playerTime += Time.deltaTime;
        }
    }

    //Count Opponent's time
    public void OpponentLapsCounter()
    {
        if (opponentLapStarted)
        {
            opponentTime += Time.deltaTime;
        }
    }

    // Update is called once per frame
    void Update()
    {
        PlayerLapsCounter();
        OpponentLapsCounter();
    }
}
