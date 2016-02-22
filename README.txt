#ClusteringImage
Program outputs groups of pictures, which are the most similar.
Firstly we form vector, which consist from only 0 (the arithmetic mean from RGB < 128) or 1 (other). Secondary, we calculate «distance» between two pictures. Thus, we form matrix and then we unite into the groups pictures, comparing their distance, after each merger, we recalculate this matrix.If you want to use this program, you must change file’s path.	
	