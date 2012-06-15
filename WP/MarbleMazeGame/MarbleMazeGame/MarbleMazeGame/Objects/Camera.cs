using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MarbleMazeGame
{
    public class Camera : GameComponent
    {
        #region Fields
        private Vector3 position = Vector3.Zero;
        private Vector3 target = Vector3.Zero;
        private GraphicsDevice graphicsDevice;

        public Vector3 ObjectToFollow { get; set; }
        public Matrix Projection { get; set; }
        public Matrix View { get; set; }

        private readonly Vector3 cameraPositionOffset = new Vector3(0, 450, 100);
        private readonly Vector3 cameraTargetOffset = new Vector3(0, 0, -50);

        #endregion

        #region Initializtion
        public Camera(Game game, GraphicsDevice graphics)
            : base(game)
        {
            this.graphicsDevice = graphics;
        }

        /// <summary>
        /// Initialize the camera
        /// </summary>
        public override void Initialize()
        {
            // Create the projection matrix
            Projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(50), graphicsDevice.Viewport.AspectRatio, 1, 10000);
            base.Initialize();
        }
        #endregion

        public override void Update(GameTime gameTime)
        {

            // Make the camera follow the object
            position = ObjectToFollow + cameraPositionOffset;

            target = ObjectToFollow + cameraTargetOffset;

            // Create the view matrix
            View = Matrix.CreateLookAt(position, target, Vector3.Up);

            base.Update(gameTime);
        }

    }

}
