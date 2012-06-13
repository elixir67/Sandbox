using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using GameStateManagement;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Input.Touch;
using Microsoft.Xna.Framework.Audio;

namespace MarbleMazeGame
{
    class GameplayScreen : GameScreen
    {
        Maze maze;
        Marble marble;
        Camera camera;

        public GameplayScreen()
        {
            TransitionOnTime = TimeSpan.FromSeconds(0.0);
            TransitionOffTime = TimeSpan.FromSeconds(0.0);
        }

        public override void LoadContent()
        {
            LoadAssets();

            base.LoadContent();
        }

        public void LoadAssets()
        {
            InitializeCamera();
            InitializeMaze();
            InitializeMarble();
        }

        private void InitializeCamera()
        {
            // Create the camera
            camera = new Camera(ScreenManager.Game, ScreenManager.GraphicsDevice);
            camera.Initialize();
        }

        private void InitializeMaze()
        {
            maze = new Maze(ScreenManager.Game)
            {
                Position = Vector3.Zero,
                Camera = camera
            };

            maze.Initialize();
        }

        private void InitializeMarble()
        {
            marble = new Marble(ScreenManager.Game)
            {
                Position = Vector3.Zero,
                Camera = camera
            };

            marble.Initialize();
        }

        public override void Update(GameTime gameTime, bool otherScreenHasFocus, bool coveredByOtherScreen)
        {
            // Update all the component of the game
            maze.Update(gameTime);
            marble.Update(gameTime);
            camera.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            ScreenManager.GraphicsDevice.Clear(Color.Black);
            ScreenManager.SpriteBatch.Begin();

            // Drawing sprites changes some render states around, which don't play
            // nicely with 3d models. 
            // In particular, we need to enable the depth buffer.
            DepthStencilState depthStensilState =
         new DepthStencilState() { DepthBufferEnable = true };
            ScreenManager.GraphicsDevice.DepthStencilState = depthStensilState;

            // Draw all the game components
            maze.Draw(gameTime);
            marble.Draw(gameTime);

            ScreenManager.SpriteBatch.End();
            base.Draw(gameTime);
        }

    }
}
