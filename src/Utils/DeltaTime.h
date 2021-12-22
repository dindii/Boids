#pragma once

namespace GLR
{
	class DeltaTime
	{
	public:
		DeltaTime();
		void tick();
		double getDeltaTime();

		operator float() { return (float)deltaTime; }

	private:
		long long int currentTime;
		long long int previousTime;
		double deltaTime;
		double secondsPerCount;
	};
}