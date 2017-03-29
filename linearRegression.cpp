#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
public:
    //传入形式为增广矩阵，加入常系数，分离结果向量
    Matrix(vector<vector<double> > &characteristic_matrix)
    {
        this->num_of_characteristic=characteristic_matrix[0].size();
        this->num_of_sample=characteristic_matrix.size();
        for(int i=0;i<num_of_sample;i++)
        {
            (this->result).push_back(characteristic_matrix[i][num_of_characteristic-1]);
            characteristic_matrix[i].pop_back();
            characteristic_matrix[i].insert(characteristic_matrix[i].begin(),1);
        }
        this->characteristic_matrix=characteristic_matrix;

        for(int i=0;i<num_of_characteristic;i++)
        {
            (this->theta).push_back(0);
        }
    }
    //特征矩阵与结果向量分开传入
    Matrix(vector<vector<double>> &characteristic_matrix,vector<double> &result)
    {
        this->num_of_characteristic=characteristic_matrix[0].size()+1;
        this->num_of_sample=characteristic_matrix.size();
        for(int i=0;i<num_of_sample;i++)
        {
            characteristic_matrix[i].insert(characteristic_matrix[i].begin(),1);
        }
        this->characteristic_matrix=characteristic_matrix;

        for(int i=0;i<this->num_of_characteristic;i++)
        {
            (this->theta).push_back(0);
        }
    }

    void printMatrix()
    {
        cout<<"num_of_characteristic:"<<num_of_characteristic<<endl;
        cout<<"num_of_sample:"<<num_of_sample<<endl;
        cout<<"matrix:"<<endl;
        for(int i=0;i<num_of_sample;i++)
        {
            for(int j=0;j<num_of_characteristic;j++)
                cout<<characteristic_matrix[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;

        cout<<"result:"<<endl;
        for(int i=0;i<num_of_sample;i++)
        {
            cout<<result[i]<<" "<<endl;;
        }
        cout<<endl;
    }

    vector<vector<double>> get_characteristic_matrix()
    {
        return characteristic_matrix;
    }
    vector<double> get_result()
    {
        return result;
    }

private:
    int num_of_characteristic;
    int num_of_sample;
    vector<vector<double> > characteristic_matrix;
    vector<double> result;
    vector<double> theta;

private:
    double err_num;
    int iteration=1500;
    double alpha=0.01;

private:
    vector<double> grand_decline()
    {
        int i,tmp;
        for(tmp=1;tmp<=iteration;tmp++)
        {
            int k;
            for(i=0;i<num_of_sample;i++)
            {
                double h=0;

                for(k=0;k<num_of_characteristic;k++)
                {
                    h=h+theta[k]*characteristic_matrix[i][k];
                }
                err_num=h-result[i];

                for(k=0;k<num_of_characteristic;k++)
                {
                    theta[k]=theta[k]-alpha*err_num*characteristic_matrix[i][k];
                }
            }
        }
        return theta;
    }

public:
    void set_iteration(int iteration)
    {

        this->iteration=iteration;
        cout<<"iteration:"<<this->iteration<<endl;
    }
    void set_alpha(double alpha)
    {

        this->alpha=alpha;
        cout<<"alpha:"<<this->alpha<<endl;
    }
    vector<double> get_theta()
    {
        return grand_decline();
    }

} ;


/*
*数据存入二维vector即可实现线性回归
*
*/
int main()
{
    vector<vector<double> > init;
    vector<double> tmp;
    tmp.push_back(1);
    tmp.push_back(3);
    tmp.push_back(4);
    init.push_back(tmp);
    tmp.clear();
    tmp.push_back(2);
    tmp.push_back(6);
    tmp.push_back(8);
    init.push_back(tmp);
    tmp.clear();
    tmp.push_back(3);
    tmp.push_back(9);
    tmp.push_back(12);
    init.push_back(tmp);
    tmp.clear();
    tmp.push_back(4);
    tmp.push_back(10);
    tmp.push_back(14);
    init.push_back(tmp);

    Matrix m(init);
    m.set_alpha(0.01);
    m.set_iteration(100000);

    //m.printMatrix();

    vector<double> theta=m.get_theta();

    cout<<"size theta[]:"<<theta.size()<<endl;

    cout<<"regression func: y="<<theta[0]<<"*x0";
    for(size_t i=1;i<theta.size();i++)
    {
        cout<<" + "<<theta[1]<<"*x"<<i;
    }
    cout<<endl;
    //cout<<theta[0]<<" *** "<<theta[1]<<endl;

    cout << "Hello world!" << endl;
    return 0;
}
