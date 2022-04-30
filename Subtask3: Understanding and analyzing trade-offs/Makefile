baseline:
	g++ baseline.cpp -o baseline -std=c++11 `pkg-config --cflags --libs opencv` 
	./baseline trafficvideo.mp4
subsampling:
	 g++ subtask3SubSampling.cpp -o subsampling -std=c++11 `pkg-config --cflags --libs opencv`
resolution:
	 g++ subtask3Resolution.cpp -o resolution -std=c++11 `pkg-config --cflags --libs opencv`
spatial:
	g++ subtask3SpatialThreads.cpp -o spatial -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
temporal:
	g++ subtask3TemporalThreads.cpp -o temporal -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
densityerror:
	g++ DensityError.cpp -o densityerror
