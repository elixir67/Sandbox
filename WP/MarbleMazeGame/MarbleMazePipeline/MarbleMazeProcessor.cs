using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content.Pipeline;
using Microsoft.Xna.Framework.Content.Pipeline.Graphics;
using Microsoft.Xna.Framework.Content.Pipeline.Processors;

namespace MarbleMazePipeline
{
    [ContentProcessor]
    public class MarbleMazeProcessor : ModelProcessor
    {
        Dictionary<string, List<Vector3>> tagData = new Dictionary<string, List<Vector3>>();

        void FindVertices(NodeContent node)
        {
            // Is this node a mesh?
            MeshContent mesh = node as MeshContent;

            if (mesh != null)
            {
                string meshName = mesh.Name;
                List<Vector3> meshVertexs = new List<Vector3>();
                // Look up the absolute transform of the mesh.
                Matrix absoluteTransform = mesh.AbsoluteTransform;
                // Loop over all the pieces of geometry in the mesh.
                foreach (GeometryContent geometry in mesh.Geometry)
                {
                    // Loop over all the indices in this piece of geometry.
                    // Every group of three indices represents one triangle.
                    foreach (int index in geometry.Indices)
                    {
                        // Look up the position of this vertex.
                        Vector3 vertex = geometry.Vertices.Positions[index];

                        // Transform from local into world space.
                        vertex = Vector3.Transform(vertex, absoluteTransform);

                        // Store this vertex.
                        meshVertexs.Add(vertex);
                    }
                }

                tagData.Add(meshName, meshVertexs);
            }

            // Recursively scan over the children of this node.
            foreach (NodeContent child in node.Children)
            {
                FindVertices(child);
            }
        }

        public override ModelContent Process(NodeContent input, ContentProcessorContext context)
        {
            FindVertices(input);

            ModelContent model = base.Process(input, context);

            model.Tag = tagData;

            return model;
        }

    }
}
