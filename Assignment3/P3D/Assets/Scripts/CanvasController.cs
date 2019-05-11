using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CanvasController : MonoBehaviour
{
    private GameObject gc;
    public Text timeText;
    bool playerIsInTheFirstLap;
    bool enemyIsInTheFirstLap;

    public Text firstPlaceName;
    public Text bestTimeFirstPlace;
    public Text secondPlaceName;
    public Text bestTimeSecondPlace;
    public Text lapOne;
    public Text lapTwo;
    public Text endGame;

    public Button mainMenu;
    public Button restart;

    bool isPaused;
    public GameObject pausePanel;

    string minSec;
    
    // Start is called before the first frame update
    void Start()
    {
        gc = GameObject.Find("GameController");
        endGame.enabled = false;
        mainMenu.gameObject.SetActive(false);
        restart.gameObject.SetActive(false);
        isPaused = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (gc.GetComponent<GameController>().playerLapStarted)
        {
            int seconds = (int)(gc.GetComponent<GameController>().playerTime % 60);
            int minutes = (int)(gc.GetComponent<GameController>().playerTime / 60) % 60;
            string timeString = string.Format("{0:00}:{1:00}", minutes, seconds);
            timeText.text = timeString;
        }

        RacePosition();
        DecideWinner();
        PauseGame();

    }

    private void Awake()
    {
        pausePanel.SetActive(false);
    }

    public void PauseGame()
    {
        if (Input.GetKeyDown(KeyCode.Escape) && !isPaused)
        {
            isPaused = true;
            Time.timeScale = 0;
            pausePanel.SetActive(true);
        }

        else if (Input.GetKeyDown(KeyCode.Escape) && isPaused)
        {
            isPaused = false;
            Time.timeScale = 1;
            pausePanel.SetActive(false);
        }
    }

    public void UnpauseButton()
    {
        isPaused = false;
        Time.timeScale = 1;
        pausePanel.SetActive(false);
    }

    public void DecideWinner()
    {
        if (gc.GetComponent<GameController>().opponentWins == true)
        {
            endGame.enabled = true;
            endGame.text = "DEFEAT";
            mainMenu.gameObject.SetActive(true);
            mainMenu.gameObject.SetActive(true);
            Time.timeScale = 0;
        }

        if (gc.GetComponent<GameController>().playerWins == true)
        {
            endGame.enabled = true;
            endGame.text = "VICTORY";
            mainMenu.gameObject.SetActive(true);
            mainMenu.gameObject.SetActive(true);
            Time.timeScale = 0;
        }
    }

    public void RacePosition()
    {
        if (gc.GetComponent<GameController>().numLapPlayer > 
            gc.GetComponent<GameController>().numLapOpponent)
        {
            firstPlaceName.text = "Player";

            if (gc.GetComponent<GameController>().numLapPlayer != 0)
            {
                int secondsaux = (int)(gc.GetComponent<GameController>().bestTimePlayer % 60);
                int minutesaux = (int)(gc.GetComponent<GameController>().bestTimePlayer / 60) % 60;
                string timeStringaux = string.Format("{0:00}:{1:00}", minutesaux, secondsaux);
                bestTimeFirstPlace.text = timeStringaux;
                lapOne.text = gc.GetComponent<GameController>().numLapPlayer.ToString();
            }
            else
            {
                bestTimeFirstPlace.text = "00:00";
            }

            secondPlaceName.text = "Enemy";

            if (gc.GetComponent<GameController>().numLapOpponent != 0)
            {
                int secondsaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent % 60);
                int minutesaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent / 60) % 60;
                string timeStringaux2 = string.Format("{0:00}:{1:00}", minutesaux2, secondsaux2);
                bestTimeSecondPlace.text = timeStringaux2;
                lapTwo.text = gc.GetComponent<GameController>().numLapOpponent.ToString();
            }
            else
            {
                bestTimeSecondPlace.text = "00:00";
            }
        }

        else if (gc.GetComponent<GameController>().numLapPlayer <
            gc.GetComponent<GameController>().numLapOpponent)
        {
            firstPlaceName.text = "Enemy";

            if (gc.GetComponent<GameController>().numLapOpponent != 0)
            {
                int secondsaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent % 60);
                int minutesaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent / 60) % 60;
                string timeStringaux2 = string.Format("{0:00}:{1:00}", minutesaux2, secondsaux2);
                bestTimeFirstPlace.text = timeStringaux2;
                lapOne.text = gc.GetComponent<GameController>().numLapOpponent.ToString();
            }
            else
            {
                bestTimeFirstPlace.text = "00:00";
            }

            secondPlaceName.text = "Player";

            if (gc.GetComponent<GameController>().numLapPlayer != 0)
            {
                int secondsaux = (int)(gc.GetComponent<GameController>().bestTimePlayer % 60);
                int minutesaux = (int)(gc.GetComponent<GameController>().bestTimePlayer / 60) % 60;
                string timeStringaux = string.Format("{0:00}:{1:00}", minutesaux, secondsaux);
                bestTimeSecondPlace.text = timeStringaux;
                lapTwo.text = gc.GetComponent<GameController>().numLapPlayer.ToString();
            }
            else
            {
                bestTimeSecondPlace.text = "00:00";
            }
        }


        if (gc.GetComponent<GameController>().numLapPlayer ==
            gc.GetComponent<GameController>().numLapOpponent)
        {
            if (gc.GetComponent<GameController>().numCheckPoint > gc.GetComponent<GameController>().numCheckPointOpponent)
            {
                firstPlaceName.text = "Player";

                if (gc.GetComponent<GameController>().numLapPlayer != 0)
                {
                    int secondsaux = (int)(gc.GetComponent<GameController>().bestTimePlayer % 60);
                    int minutesaux = (int)(gc.GetComponent<GameController>().bestTimePlayer / 60) % 60;
                    string timeStringaux = string.Format("{0:00}:{1:00}", minutesaux, secondsaux);
                    bestTimeFirstPlace.text = timeStringaux;
                    lapOne.text = gc.GetComponent<GameController>().numLapPlayer.ToString();
                }
                else
                {
                    bestTimeFirstPlace.text = "00:00";
                }

                secondPlaceName.text = "Enemy";

                if (gc.GetComponent<GameController>().numLapOpponent != 0)
                {
                    int secondsaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent % 60);
                    int minutesaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent / 60) % 60;
                    string timeStringaux2 = string.Format("{0:00}:{1:00}", minutesaux2, secondsaux2);
                    bestTimeSecondPlace.text = timeStringaux2;
                    lapTwo.text = gc.GetComponent<GameController>().numLapOpponent.ToString();
                }
                else
                {
                    bestTimeSecondPlace.text = "00:00";
                }
            }

            else if (gc.GetComponent<GameController>().numCheckPoint < gc.GetComponent<GameController>().numCheckPointOpponent)
            {
                firstPlaceName.text = "Enemy";

                if (gc.GetComponent<GameController>().numLapOpponent != 0)
                {
                    int secondsaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent % 60);
                    int minutesaux2 = (int)(gc.GetComponent<GameController>().bestTimeOpponent / 60) % 60;
                    string timeStringaux2 = string.Format("{0:00}:{1:00}", minutesaux2, secondsaux2);
                    bestTimeFirstPlace.text = timeStringaux2;
                    lapOne.text = gc.GetComponent<GameController>().numLapOpponent.ToString();
                }
                else
                {
                    bestTimeFirstPlace.text = "00:00";
                }

                secondPlaceName.text = "Player";

                if (gc.GetComponent<GameController>().numLapPlayer != 0)
                {
                    int secondsaux = (int)(gc.GetComponent<GameController>().bestTimePlayer % 60);
                    int minutesaux = (int)(gc.GetComponent<GameController>().bestTimePlayer / 60) % 60;
                    string timeStringaux = string.Format("{0:00}:{1:00}", minutesaux, secondsaux);
                    bestTimeSecondPlace.text = timeStringaux;
                    lapTwo.text = gc.GetComponent<GameController>().numLapPlayer.ToString();
                }
                else
                {
                    bestTimeSecondPlace.text = "00:00";
                }
            }


        }
    }

 
}
