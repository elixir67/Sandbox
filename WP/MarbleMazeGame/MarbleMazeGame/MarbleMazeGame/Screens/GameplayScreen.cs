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
using Microsoft.Devices;

namespace MarbleMazeGame
{
    class GameplayScreen : GameScreen
    {
        Maze maze;
        Marble marble;
        Camera camera;
        readonly float angularVelocity = MathHelper.ToRadians(1.5f);
        Vector3? accelerometerState = Vector3.Zero;
        bool gameOver = false;
        LinkedListNode<Vector3> lastCheackpointNode;
        SpriteFont timeFont;
        TimeSpan gameTime;

        public GameplayScreen()
        {
            TransitionOnTime = TimeSpan.FromSeconds(0.0);
            TransitionOffTime = TimeSpan.FromSeconds(0.0);
        }

        public override void LoadContent()
        {
            LoadAssets();
            timeFont = ScreenManager.Game.Content.Load<SpriteFont>(@"Fonts\MenuFont");
            Accelerometer.Initialize();
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

            // Save the last checkpoint
            lastCheackpointNode = maze.Checkpoints.First;
        }

        private void InitializeMarble()
        {
            marble = new Marble(ScreenManager.Game as MarbleMazeGame)
            {
                Position = maze.StartPoistion,
                Camera = camera,
                Maze = maze
            };
            marble.Initialize();
        }

        public override void Update(GameTime gameTime, bool otherScreenHasFocus, bool coveredByOtherScreen)
        {
            // Calculate the time from the start of the game
            this.gameTime += gameTime.ElapsedGameTime;

            CheckFallInPit();
            UpdateLastCheackpoint();

            // Update all the component of the game
            maze.Update(gameTime);
            marble.Update(gameTime);
            camera.Update(gameTime);

            CheckGameFinish();

            base.Update(gameTime, otherScreenHasFocus, coveredByOtherScreen);

        }

        private void UpdateLastCheackpoint()
        {
            BoundingSphere marblePosition = marble.BoundingSphereTransformed;

            var tmp = lastCheackpointNode;
            while (tmp.Next != null)
            {
                // If the marble is close to a checkpoint save the checkpoint
                if (Math.Abs(Vector3.Distance(marblePosition.Center, tmp.Next.Value))
                    <= marblePosition.Radius * 3)
                {
                    AudioManager.PlaySound("checkpoint");
                    lastCheackpointNode = tmp.Next;
                    return;
                }
                tmp = tmp.Next;
            }
        }

        private void CheckFallInPit()
        {
            if (marble.Position.Y < -150)
            {
                marble.Position = lastCheackpointNode.Value;
                maze.Rotation = Vector3.Zero;
                marble.Acceleration = Vector3.Zero;
                marble.Velocity = Vector3.Zero;
            }
        }

        private void CheckGameFinish()
        {
            BoundingSphere marblePosition = marble.BoundingSphereTransformed;

            if (Math.Abs(Vector3.Distance(marblePosition.Center, maze.End)) <=
                marblePosition.Radius * 3)
            {
                gameOver = true;
                return;
            }
        }

        public override void Draw(GameTime gameTime)
        {
            ScreenManager.GraphicsDevice.Clear(Color.Black);
            ScreenManager.SpriteBatch.Begin();

            // Draw the elapsed time
            ScreenManager.SpriteBatch.DrawString(timeFont,
                String.Format("{0:00}:{1:00}", this.gameTime.Minutes,
                this.gameTime.Seconds), new Vector2(20, 20), Color.YellowGreen);

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


        public override void HandleInput(InputState input)
        {
            if (input == null)
                throw new ArgumentNullException("input");

            // Rotate the maze according to accelerometer data
            Vector3 currentAccelerometerState = Accelerometer.GetState().Acceleration;

            if (Microsoft.Devices.Environment.DeviceType == DeviceType.Device)
            {
                //Change the velocity according to acceleration reading
                maze.Rotation.Z = (float)Math.Round(MathHelper.ToRadians(currentAccelerometerState.Y * 30), 2);
                maze.Rotation.X = -(float)Math.Round(MathHelper.ToRadians(currentAccelerometerState.X * 30), 2);
            }
            else if (Microsoft.Devices.Environment.DeviceType == DeviceType.Emulator)
            {
                Vector3 Rotation = Vector3.Zero;

                if (currentAccelerometerState.X != 0)
                {
                    if (currentAccelerometerState.X > 0)
                        Rotation += new Vector3(0, 0, -angularVelocity);
                    else
                        Rotation += new Vector3(0, 0, angularVelocity);
                }

                if (currentAccelerometerState.Y != 0)
                {
                    if (currentAccelerometerState.Y > 0)
                        Rotation += new Vector3(-angularVelocity, 0, 0);
                    else
                        Rotation += new Vector3(angularVelocity, 0, 0);
                }

                // Limit the rotation of the maze to 30 degrees
                maze.Rotation.X =
                    MathHelper.Clamp(maze.Rotation.X + Rotation.X,
                    MathHelper.ToRadians(-30), MathHelper.ToRadians(30));

                maze.Rotation.Z =
                    MathHelper.Clamp(maze.Rotation.Z + Rotation.Z,
                    MathHelper.ToRadians(-30), MathHelper.ToRadians(30));

            }
        }

    }

}
