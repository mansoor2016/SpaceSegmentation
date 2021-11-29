# SpaceSegmentation

<WIP>

Reads an input file formatted as:

<no. of lines>
<min coord> <max coord>
<min coord> <max coord>
....

which defines a set of non-overlaping axis aligned boxes, see ExampleInputs.txt.

These boxes, which can encompass but not intersect each other, defined regions
which are either classified as Land or Sea. Land is defined as any region 
contained only by an unbounded region, or inside a Sea region. Two adjacent
regions cannot share the same classification. So the largest region is therefore
a land region, any immediately contained regions will be Sea regions, and regions 
immediately contained within those Sea regions are Land regions.

## ToDo

 Implement test coverage