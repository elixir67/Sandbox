#region Using Statements
using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Input.Touch;
using Microsoft.Xna.Framework.Media;
using CatapultGame;
using GameStateManagement;
using Microsoft.Phone.Shell;
using System.IO.IsolatedStorage;
using System.Xml.Serialization;
using System.IO;
using Microsoft.Phone.Tasks;
#endregion


namespace CatapultGame
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class CatapultGame : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        ScreenManager screenManager;
        string fileName = "Catapult.dat";
        PhoneNumberChooserTask phoneNumberChooserTask;
        SmsComposeTask smsComposeTask;

        public CatapultGame()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            // Frame rate is 30 fps by default for Windows Phone.
            TargetElapsedTime = TimeSpan.FromTicks(333333);

            //Create a new instance of the Screen Manager
            screenManager = new ScreenManager(this);
            Components.Add(screenManager);

            //Switch to full screen for best game experience
            graphics.IsFullScreen = true;

            //Add two new screens
            screenManager.AddScreen(new BackgroundScreen(), null);
            screenManager.AddScreen(new MainMenuScreen(), null);

            //Create Chooser and Launcher
            InitializeChooserAndLauncher();

            AudioManager.Initialize(this);
            InitializePhoneServices();
        }

        protected override void LoadContent()
        {
            AudioManager.LoadSounds();
            base.LoadContent();
        }

        private void InitializePhoneServices()
        {
            PhoneApplicationService.Current.Activated += new EventHandler<ActivatedEventArgs>(GameActivated);
            PhoneApplicationService.Current.Deactivated += new EventHandler<DeactivatedEventArgs>(GameDeactivated);
            PhoneApplicationService.Current.Closing += new EventHandler<ClosingEventArgs>(GameClosing);
            PhoneApplicationService.Current.Launching += new EventHandler<LaunchingEventArgs>(GameLaunching);
        }

        private void InitializeChooserAndLauncher()
        {
            phoneNumberChooserTask = new PhoneNumberChooserTask();
            smsComposeTask = new SmsComposeTask();
            phoneNumberChooserTask.Completed += new EventHandler<PhoneNumberResult>(PhoneNumberChooserTaskCompleted);
        }

        #region Event Handlers
        /// <summary>
        /// Occurs when the Phone Number Chooser task completes
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        void PhoneNumberChooserTaskCompleted(object sender, PhoneNumberResult args)
        {
            // If user provided the requested info
            if (args.TaskResult == TaskResult.OK)
            {
                // Create, initialize and show SMS composer launcher
                smsComposeTask.To = args.PhoneNumber;
                smsComposeTask.Body =
                    "Hello! Just discovered very good game called Catapult Wars. Try it by yourself and see!";
                smsComposeTask.Show();
            }
        }

        /// <summary>
        /// Occurs when the game class (and application) launched
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void GameLaunching(object sender, LaunchingEventArgs e)
        {
            ReloadLastGameState(false);
        }

        /// <summary>
        /// Occurs when the game class (and application) exiting during exit cycle
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void GameClosing(object sender, ClosingEventArgs e)
        {
            SaveActiveGameState(false);
        }

        /// <summary>
        /// Occurs when the game class (and application) deactivated and tombstoned
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void GameDeactivated(object sender, DeactivatedEventArgs e)
        {
            SaveActiveGameState(true);
        }

        /// <summary>
        /// Occurs when the game class (and application) activated during return from tombstoned state
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void GameActivated(object sender, ActivatedEventArgs e)
        {
            ReloadLastGameState(true);
        }
        #endregion

        #region Private functionality
        /// <summary>
        /// Reload last active game state from Isolated Storage or State object
        /// </summary>
        /// <param name="isTombstoning"></param>
        private void ReloadLastGameState(bool isTombstoning)
        {
            int playerScore = 0;
            int computerScore = 0;
            bool isHumanTurn = false;
            bool isLoaded = false;

            if (isTombstoning)
                isLoaded = LoadFromStateObject(out playerScore, out computerScore, out isHumanTurn);
            else
            {
                isLoaded = LoadFromIsolatedStorage(ref playerScore, ref computerScore, ref isHumanTurn);

                if (isLoaded)
                {
                    if (System.Windows.MessageBox.Show("Old game available.\nDo you want to continue last game?", "Load Game", System.Windows.MessageBoxButton.OKCancel) == System.Windows.MessageBoxResult.OK)
                        isLoaded |= true;
                    else
                        isLoaded = false;
                }
            }

            if (isLoaded)
            {
                PhoneApplicationService.Current.State.Add("playerScore", playerScore);
                PhoneApplicationService.Current.State.Add("computerScore", computerScore);
                PhoneApplicationService.Current.State.Add("isHumanTurn", isHumanTurn);

                GameplayScreen gameplayScreen = new GameplayScreen();
                screenManager.AddScreen(gameplayScreen, null);
            }
        }

        private bool LoadFromIsolatedStorage(ref int playerScore, ref int computerScore, ref bool isHumanTurn)
        {
            bool res = true; // Assume success

            // Load from Isolated Storage file
            using (IsolatedStorageFile isolatedStorageFile
                = IsolatedStorageFile.GetUserStoreForApplication())
            {
                if (isolatedStorageFile.FileExists(fileName))
                {
                    //If user choose to save, create a new file
                    using (IsolatedStorageFileStream fileStream
                        = isolatedStorageFile.OpenFile(fileName, FileMode.Open))
                    {
                        using (StreamReader streamReader = new StreamReader(fileStream))
                        {
                            playerScore = int.Parse(streamReader.ReadLine(),
                                                    System.Globalization.NumberStyles.Integer);
                            computerScore = int.Parse(streamReader.ReadLine(),
                                                        System.Globalization.NumberStyles.Integer);
                            isHumanTurn = bool.Parse(streamReader.ReadLine());
                            streamReader.Close();
                        }
                    }

                    res = true;
                    isolatedStorageFile.DeleteFile(fileName);
                }
                else
                    res = false;
            }

            return res;
        }

        private bool LoadFromStateObject(out int playerScore, out int computerScore, out bool isHumanTurn)
        {
            playerScore = -1;
            computerScore = -1;
            isHumanTurn = false;
            bool res = true; // Assume success

            if (PhoneApplicationService.Current.State.ContainsKey("HumanScore"))
            {
                playerScore = (int)PhoneApplicationService.Current.State["HumanScore"];
                PhoneApplicationService.Current.State.Remove("HumanScore");
            }
            else
                res = false;

            if (PhoneApplicationService.Current.State.ContainsKey("PhoneScore"))
            {
                computerScore = (int)PhoneApplicationService.Current.State["PhoneScore"];
                PhoneApplicationService.Current.State.Remove("PhoneScore");
            }
            else res = false;

            if (PhoneApplicationService.Current.State.ContainsKey("isHumanTurn"))
            {
                isHumanTurn = (bool)PhoneApplicationService.Current.State["isHumanTurn"];
                PhoneApplicationService.Current.State.Remove("isHumanTurn");
            }
            else
                res = false;

            return res;
        }

        /// <summary>
        /// Saves the current game state (if game is running) to Isolated Storage or State object
        /// </summary>
        /// <param name="isTombstoning"></param>
        private void SaveActiveGameState(bool isTombstoning)
        {
            // Try finding the running game instance 
            var res = from screen in screenManager.GetScreens()
                      where screen.GetType() == typeof(GameplayScreen)
                      select screen;

            GameplayScreen gameplayScreen = res.FirstOrDefault() as GameplayScreen;

            if (null != gameplayScreen)
            {
                if (isTombstoning)
                {
                    SaveToStateObject(gameplayScreen);
                }
                else
                {
                    SaveToIsolatedStorageFile(gameplayScreen, fileName);
                }
            }
        }

        /// <summary>
        /// Saves the gameplay screen data to Isolated storage file
        /// </summary>
        /// <param name="gameplayScreen"></param>
        /// <param name="fileName"></param>
        private void SaveToIsolatedStorageFile(GameplayScreen gameplayScreen, string fileName)
        {
            // Save to Isolated Storage file
            using (IsolatedStorageFile isolatedStorageFile
                = IsolatedStorageFile.GetUserStoreForApplication())
            {
                // If user choose to save, create a new file
                using (IsolatedStorageFileStream fileStream
                    = isolatedStorageFile.CreateFile(fileName))
                {
                    using (StreamWriter streamWriter = new StreamWriter(fileStream))
                    {
                        // Write date to the file
                        streamWriter.WriteLine(gameplayScreen.player.Score);
                        streamWriter.WriteLine(gameplayScreen.computer.Score);
                        streamWriter.WriteLine(gameplayScreen.isHumanTurn);
                        streamWriter.Close();
                    }
                }
            }
        }

        /// <summary>
        /// Saves the gameplay screen data to State Object
        /// </summary>
        /// <param name="gameplayScreen"></param>
        private static void SaveToStateObject(GameplayScreen gameplayScreen)
        {
            // Save date to the State object
            PhoneApplicationService.Current.State.Add("HumanScore", gameplayScreen.player.Score);
            PhoneApplicationService.Current.State.Add("PhoneScore", gameplayScreen.computer.Score);
            PhoneApplicationService.Current.State.Add("isHumanTurn", gameplayScreen.isHumanTurn);
        }
        #endregion

        #region Public Interface
        public void ExecuteTask()
        {
            phoneNumberChooserTask.Show();
        }
        #endregion

    }
}
