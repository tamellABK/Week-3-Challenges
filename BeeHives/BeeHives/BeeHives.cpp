#include <iostream>
#include <thread>
#include <time.h>
#include <chrono>
#include <mutex>

using namespace std;

int const HONEY_MAX_SECONDS = 15;
int const HONEY_MIN_SECONDS = 5;
int const FARMER_CHECK_INTERVAL = 10;

mutex Mutex;

bool quitProducingHoney = false;

void HiveActivity(bool* sendHoneyToPickup);
void FarmerActivity(bool* collectHoney, int* honeyCount);

int main()
{
	bool honeyToPickup = false;
	int honeyCount = 0;

	cout << "Starting Honey Production!\n\n";

	thread Hive1(HiveActivity, &honeyToPickup);
	thread Hive2(HiveActivity, &honeyToPickup);
	thread Hive3(HiveActivity, &honeyToPickup);
	thread Farmer(FarmerActivity, &honeyToPickup, &honeyCount);

	Farmer.join();
}

void FarmerActivity(bool* checkHoney, int* honeyCount)
{
	chrono::system_clock::time_point startTime = chrono::system_clock::now();
	while (!quitProducingHoney)
	{
		chrono::system_clock::time_point currentTime = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = currentTime - startTime;

		lock_guard<mutex> Guard(Mutex);
		if (elapsed_seconds.count() >= FARMER_CHECK_INTERVAL && *checkHoney)
		{
			*honeyCount += 1;
			*checkHoney = false;
			cout << "Farmer Picked Up The Honey! ::: Count: " << *honeyCount << endl;
			startTime = chrono::system_clock::now();

		}
	}
}

void HiveActivity(bool* sendHoneyToPickup)
{
	srand(chrono::steady_clock::now().time_since_epoch().count());

	bool honeyProduced = false;
	chrono::system_clock::time_point startTime = chrono::system_clock::now();
	int timeToProduce = rand() % (HONEY_MAX_SECONDS - HONEY_MIN_SECONDS) + HONEY_MIN_SECONDS;
	
	while (!quitProducingHoney)
	{

		if (!honeyProduced)
		{
			chrono::system_clock::time_point currentTime = chrono::system_clock::now();
			chrono::duration<double> elapsed_seconds = currentTime - startTime;

			if (elapsed_seconds.count() >= timeToProduce)
			{
				cout << "Honey Produced After " << timeToProduce << " Seconds!" << endl;
				honeyProduced = true;
				timeToProduce = rand() % (HONEY_MAX_SECONDS - HONEY_MIN_SECONDS) + HONEY_MIN_SECONDS;
				startTime = chrono::system_clock::now();
			}
		}
		else
		{
			lock_guard<mutex> Guard(Mutex);
			if (!*sendHoneyToPickup)
			{
				cout << "Honey Sent!" << endl;
				*sendHoneyToPickup = true;
				honeyProduced = false;
			}
		}

	}
}