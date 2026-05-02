using System;
var raw = Console.ReadLine();
var n = string.IsNullOrWhiteSpace(raw) ? 42 : int.Parse(raw);
Console.WriteLine($"binary {Convert.ToString(n, 2)}");
Console.WriteLine($"hex {Convert.ToString(n, 16).ToUpper()}");
