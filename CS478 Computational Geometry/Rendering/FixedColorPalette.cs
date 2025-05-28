using System.Collections.Generic;
using UnityEngine;

public static class FixedColorPalette
{
    private static List<Color> palette = GenerateColorSet();
    private static int currentIndex = 0;

    public static Color GetNextColor()
    {
        Color color = palette[currentIndex];
        currentIndex = (currentIndex + 1) % palette.Count;
        return color;
    }
    public static void Reset()
    {
        currentIndex = 0;
    }

  
    private static List<Color> GenerateColorSet()
    {
        List<Color> result = new List<Color>();
        float goldenRatio = 0.61803398875f;
        float hue = 0f;

        for (int i = 0; i < 60; i++) // feel free to increase this number
        {
            hue += goldenRatio;
            hue %= 1f;
            float saturation = 0.75f;
            float value = 0.95f;
            result.Add(Color.HSVToRGB(hue, saturation, value));
        }

        return result;
    }
}
