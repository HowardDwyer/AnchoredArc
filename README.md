# AnchoredArc
Code sample and example of an algorithm write up.
The algorithm finds a least squares circle through a set of points which passes through two specified points - 
that is, the circle is "anchored" to two specified points and is a least squares fit for any number (at least one)
of other points.

The least squares objective function is different than usual for a circle fit, resulting in a closed-form formula; no 
search or iteration is involved.
