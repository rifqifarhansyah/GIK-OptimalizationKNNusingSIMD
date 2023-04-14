#include <bits/stdc++.h>
#include <iostream>
#include <emmintrin.h>
#include <sys/time.h>
#include <chrono>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ostream> 
#include <sstream>

using namespace std;

class Point {
    public:
        Point() {}
        Point(const vector<double>& coords) : _coords(coords) {}
        virtual ~Point() {}
        double getDist(const Point &other) const {
            double sum = 0.0;
            for (int i = 0; i < _coords.size(); i++) {
                double diff = _coords[i] - other._coords[i];
                sum += diff * diff;
            }
            return sqrt(sum);
        }
        const vector<double>& getCoords() const {
            return _coords;
        }
        bool operator<(const Point& other) const {
            return _coords[0] < other._coords[0];
        }
    private:
        vector<double> _coords;
};

class PointSIMD{
    public:
    PointSIMD() {}
    PointSIMD(const vector<double>& coords) : _coords(coords) {}
    virtual ~PointSIMD() {}

    double getDist(const PointSIMD& other) const {
        double sum = 0.0;
        const int size = _coords.size();

        // Inisialisasi register SIMD dengan nilai 0
        __m128d diff_sum = _mm_set1_pd(0.0);

        // Loop melalui koordinat dalam blok dengan keliipatan 4
        for (int i = 0; i < size; i += 4) {
            // Load empat koordinat dari PointSIMD
            __m128d this_coords = _mm_loadu_pd(&_coords[i]);

            // Load empat koordinat dari PointSIMD lainnya
            __m128d other_coords = _mm_loadu_pd(&(other._coords[i]));

            // Hitung selisih antara koordinat
            __m128d diff = _mm_sub_pd(this_coords, other_coords);

            // Hitung kuadrat dari selisih
            __m128d square_diff = _mm_mul_pd(diff, diff);

            // Tambahkan kuadrat selisih ke jumlah yang sedang berjalan
            diff_sum = _mm_add_pd(diff_sum, square_diff);
        }

        // Reduce the SIMD register to a scalar value
        double diff_array[4];
        _mm_storeu_pd(diff_array, diff_sum);

        for (int i = 0; i < 4; ++i) {
            sum += diff_array[i];
        }

        // Finish the distance calculation
        for (int i = size - (size % 4); i < size; ++i) {
            double diff = _coords[i] - other._coords[i];
            sum += diff * diff;
        }

        return sqrt(sum);
    }

    const vector<double>& getCoords() const {
        return _coords;
    }

    bool operator<(const PointSIMD& other) const {
        return _coords[0] < other._coords[0];
    }

    private:
        vector<double> _coords;
};

class NearestPointsContainer{
    public:
        NearestPointsContainer() {}
        virtual ~NearestPointsContainer() {}
        
        void addPoints(const Point &points){
            _points.push_back(points);
        }

        bool comparePoints(const Point &p1, const Point &p2, const Point &target_point) {
            return p1.getDist(target_point) < p2.getDist(target_point);
        }

        
        bool getNearestPoints(const Point &target_point,vector<Point> &nearest_points,int K){
            // PriorityQueue untuk menyimpan k titik terdekat
            priority_queue<pair<double, Point>> nearest_points_pqueue;

            if(K>_points.size()){ // Jika nilai K lebih besar dari jumlah titik yang ada, maka tidak ada titik terdekat yang dapat ditemukan.
                return false;
            }

            ofstream near_points_file("near_points_file.txt"); // Membuat file untuk menyimpan titik terdekat
            near_points_file << "Kumpulan titik :"<<endl;
            for(auto itr = _points.begin(); itr != _points.end(); ++itr){
                double current_point_distance= itr->getDist(target_point);
                // buatkan fungsi untuk menulis near_points_file ke txt
                for(int i=0; i<itr->getCoords().size(); i++){
                    near_points_file << itr->getCoords()[i]<<" ";
                }
                near_points_file << endl;
                if(nearest_points_pqueue.size()<K){
                    nearest_points_pqueue.push({current_point_distance, *itr});
                }else{
                    double highest_distance = nearest_points_pqueue.top().first;
                    if(comparePoints(*itr, nearest_points_pqueue.top().second, target_point)){
                        nearest_points_pqueue.pop();
                        nearest_points_pqueue.push({current_point_distance, *itr});
                    }
                }
            }
            near_points_file << endl;
            near_points_file << "Kumpulan titik terdekat :"<<endl;
            while(!nearest_points_pqueue.empty()){
                Point close_point = nearest_points_pqueue.top().second;
                nearest_points.push_back(close_point);
                for(int i=0; i<close_point.getCoords().size(); i++){
                    near_points_file << close_point.getCoords()[i]<<" ";
                }
                near_points_file << endl;
                nearest_points_pqueue.pop();
            }
            near_points_file << endl;
            near_points_file << "Target Point :" << endl;
            for(int i=0; i<target_point.getCoords().size(); i++){
                near_points_file << target_point.getCoords()[i]<<" ";
            }
            near_points_file << endl;
            near_points_file.close();       
            return true;
        }
    private:
        typedef vector<Point> Points;
        Points _points;
};

class NearestPointsContainerSIMD{
    public:
        NearestPointsContainerSIMD() {}
        virtual ~NearestPointsContainerSIMD() {}
        
        void addPoints(const PointSIMD &point){
            _points.push_back(point);
        }

        bool comparePoints(const PointSIMD &p1, const PointSIMD &p2, const PointSIMD &target_point) {
            return p1.getDist(target_point) < p2.getDist(target_point);
        }

        bool getNearestPoints(const PointSIMD &target_point, vector<PointSIMD> &nearest_points, int k){
            // PriorityQueue to store k nearest points
            priority_queue<pair<double, PointSIMD>> nearest_points_pqueue;

            if(k > _points.size()){ // If k is greater than the number of points, there are no nearest points to be found.
                return false;
            }

            ofstream near_points_file("near_points_file.txt"); // Create a file to store the nearest points
            near_points_file << "Set of points:" << endl;
            for(auto itr = _points.begin(); itr != _points.end(); ++itr){
                double current_point_distance = itr->getDist(target_point);
                // write to near_points_file
                for(int i = 0; i < itr->getCoords().size(); i++){
                    near_points_file << itr->getCoords()[i] << " ";
                }
                near_points_file << endl;
                if(nearest_points_pqueue.size() < k){
                    nearest_points_pqueue.push({current_point_distance, *itr});
                } else {
                    double highest_distance = nearest_points_pqueue.top().first;
                    if(comparePoints(*itr, nearest_points_pqueue.top().second, target_point)){
                        nearest_points_pqueue.pop();
                        nearest_points_pqueue.push({current_point_distance, *itr});
                    }
                }
            }
            near_points_file << endl;
            near_points_file << "Set of nearest points:" << endl;
            while(!nearest_points_pqueue.empty()){
                PointSIMD close_point = nearest_points_pqueue.top().second;
                nearest_points.push_back(close_point);
                for(int i = 0; i < close_point.getCoords().size(); i++){
                    near_points_file << close_point.getCoords()[i] << " ";
                }
                near_points_file << endl;
                nearest_points_pqueue.pop();
            }
            near_points_file << endl;
            near_points_file << "Target Point:" << endl;
            for(int i = 0; i < target_point.getCoords().size(); i++){
                near_points_file << target_point.getCoords()[i] << " ";
            }
            near_points_file << endl;
            near_points_file.close();
            return true;
        }

    private:
        vector<PointSIMD> _points;
};

int main(int argc, const char * argv[]) {
    const int RANDOM_POINTS_MAX_VALUE = 100; // Nilai maksimal dari titik yang akan dihasilkan secara random
    const int RANDOM_POINTS_COUNT = 1000; // Nilai jumlah titik yang akan dihasilkan secara random
    std::mt19937 eng; // Deklarasi variabel eng untuk menyimpan nilai random 
    eng.seed(std::random_device{}());
    // Membuat distribusi random untuk nilai X dan Y dari titik yang akan dihasilkan secara random
    std::uniform_int_distribution<> dist(-RANDOM_POINTS_MAX_VALUE, RANDOM_POINTS_MAX_VALUE);
    int dimensi;
    vector<double> pointContainer;
    int K;
    // berikan warna pada terminal
    cout << "\033[1;32m" << "====================================================="<< endl;
    cout << "Masukkan nilai dimensi\t\t\t: ";
    cin >> dimensi;
    cout << "Masukkan nilai Poin\t\t\t: ";
    for(int i=0; i<dimensi; i++){
        double point;
        cin >> point;
        pointContainer.push_back(point);
    }
    cout << "Masukkan nilai K(1 s.d. 1000)\t\t: ";
    cin >> K; 
    cout << "====================================================="<< "\033[0m" << endl;

    NearestPointsContainer points_container;
    NearestPointsContainerSIMD points_container_simd;
    for(int i=0; i<RANDOM_POINTS_COUNT; i++){
        vector<double> point;
        for(int j=0; j<dimensi; j++){
            point.push_back(dist(eng));
        }
        points_container.addPoints(Point(point));
        points_container_simd.addPoints(PointSIMD(point));
    }
    Point target_point(pointContainer);
    vector<Point> nearest_points;
    struct timespec start, end, start1, end1;
    // calculate time taken by scalar search
    clock_gettime(CLOCK_MONOTONIC, &start);
    ios_base::sync_with_stdio(false);
    points_container.getNearestPoints(target_point, nearest_points, K);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_tiken_withoutSIMD = (end.tv_sec - start.tv_sec) * 1e9;
    time_tiken_withoutSIMD = (time_tiken_withoutSIMD + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    cout << "\033[1;33m"; 
    int i=1; // Deklarasi untuk menampilkan nomor titik terdekat
    for( auto itr = nearest_points.begin(); itr != nearest_points.end(); ++itr){
        cout << "Titik Terdekat ke-"<<i<<" : ";
        for(int j=0; j<dimensi; j++){
            cout << itr->getCoords()[j] << " ";
        }
        cout << endl;
        i++;
    }
    cout << "\033[0m" << endl;

    PointSIMD target_point_simd(pointContainer);
    vector<PointSIMD> nearest_points_simd;
    // calculate time taken by SIMD search
    clock_gettime(CLOCK_MONOTONIC, &start1);
    ios_base::sync_with_stdio(false);
    points_container_simd.getNearestPoints(target_point_simd, nearest_points_simd, K);
    clock_gettime(CLOCK_MONOTONIC, &end1);
    double time_tiken_withSIMD = (end1.tv_sec - start1.tv_sec) * 1e9;
    time_tiken_withSIMD = (time_tiken_withSIMD + (end1.tv_nsec - start1.tv_nsec)) * 1e-9;
    cout << "\033[1;33m";
    int x=1; // Deklarasi untuk menampilkan nomor titik terdekat
    for( auto itr = nearest_points_simd.begin(); itr != nearest_points_simd.end(); ++itr){
        cout << "Titik Terdekat ke-"<<x<<" : ";
        for(int j=0; j<dimensi; j++){
            cout << itr->getCoords()[j] << " ";
        }
        cout << endl;
        i++;
    }
    cout << endl;
    cout << "Time taken without SIMD\t\t: " << fixed << time_tiken_withoutSIMD << setprecision(9) << " seconds" << endl;
    cout << "Time taken with SIMD\t\t: " << fixed << time_tiken_withSIMD << setprecision(9) << " seconds" << endl;
    cout << "\033[0m";
    cout<<endl;
    return 0;
}