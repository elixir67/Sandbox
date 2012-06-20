// ----------------------------------------------------------------------------------
// Microsoft Developer & Platform Evangelism
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
// EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
// ----------------------------------------------------------------------------------
// The example companies, organizations, products, domain names,
// e-mail addresses, logos, people, places, and events depicted
// herein are fictitious.  No association with any real company,
// organization, product, domain name, email address, logo, person,
// places, or events is intended or should be inferred.
// ----------------------------------------------------------------------------------

#region File Description
//-----------------------------------------------------------------------------
// IntersectDetails.cs
//
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#endregion

#region Using Statements
using System;
using System.Collections.Generic;
#endregion

namespace MarbleMazeGame
{
    public struct IntersectDetails
    {
        #region Fields
        public bool IntersectWithGround;
        public bool IntersectWithFloorSides;
        public bool IntersectWithWalls;

        public Triangle IntersectedGroundTriangle;
        public IEnumerable<Triangle> IntersectedFloorSidesTriangle;
        public IEnumerable<Triangle> IntersectedWallTriangle; 
        #endregion
    }
}