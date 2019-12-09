"""
	Submission out of contest time

	- This solution does not discuss any combinatorial meaning. It only gives a simple way to "guess" the answer
	  for a simple-looking problem with simple input and output in a contest setting.

	- If you are familiar with profile DP, there is a clear 3^R*R*C solution.
	  This does not look fast enough, but maybe it will pass anyway. I would love to know :)

	- If we want to construct any solution, let's fill up columns by columns.
	  Each next column of squares is only restricted by the rightmost colors of the previous column.
	  So we can construct a solution by starting with any single strip of R colors, then choose C next color strips.
	
	- This approach suggest that, suppose we fix any parameter, there is a recurrence on the other that gives us the answer.
	  For C = 0, there are exactly 3^R starting color strips -> F(R, 0) = 3^R.
	  For R = 1, the sample gives the recurrence F(1, C) = 6*F(1, C-1).
	  Can be easily proven correct.

	- How do we generalize for larger C? 
	  We know F(R, C) = F(C, R), so we already have F(2, 0) and F(2, 1) previously calculated. 
	  F(0, 2) = F(2, 0) = 3^2 = 9.
	  F(1, 2) = F(2, 1) = 108 (from sample test).
	  This suggests a recurrence F(2, C) = 12*F(2, C-1).

	- At this point we have 
		+ F(0, C) = 3*F(0, C-1) (= 3^C)
		+ F(1, C) = 6*F(1, C-1)
		+ F(2, C) = 12*F(2, C-1)
	- We can now "guess" the remaining parameter: F(R, C) = 3*2^R * F(R, C-1)
	  The base case with F(R, 0) = 3^R
	  This gives the formula F(R, C) = 3^R * [3*(2^R)]^C
"""

t = int(input())
while (t > 0):
	t -= 1
	r, c = map(int, input().split())
	print(pow(3, r, 1000000007) * pow(3*pow(2, r, 1000000007), c, 1000000007) % 1000000007)