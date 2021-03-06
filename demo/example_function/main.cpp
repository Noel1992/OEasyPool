/**
* @author : 陈鲁勇
* @date   : 2017年04月
* @version: 1.0
* @note   : 根据 Apache 许可证 2.0 版（以下简称“许可证”）授权;
*           除非遵守本许可，否则您不能使用这个文件。
* @remarks: 您可以获得该许可的副本：
*           http://www.apache.org/licenses/LICENSE-2.0
*           除非适用法律需要或者书面同意，按本许可分发的软件
*           要按“原样”分发，没有任何形式的，明确或隐含的担保条款。
*           参见按照本许可控制许可权限及限制的特定语言的许可证。
*
*   你可以获得该代码的最新版本：
*
*        http://git.oschina.net/Mr_ChenLuYong/oeasypool
*
*   开源社区的所有人都期待与你的共同维护。
*
*
*   如果你对这些代码还有不理解的地方可以通过最新的文章进行学习：
*
*        博客地址：http://blog.csdn.net/csnd_ayo
*
*        文章地址：http://blog.csdn.net/csnd_ayo/article/details/72457190
*
* 	 期待你提交Bug，欢迎Issues。
*
*/

#include <time.h>
#include <iostream>
#include <memory>
#include <string>
#include "OE/EasyThreadPool"

#include "../../test/OEFunctionTask.h"



using namespace std;



int vFunction(void) {
    std::cout << __FUNCTION__ << std::endl;
    return 0;
}


int hello(int a, std::string b) {
    std::cout << __FUNCTION__ << " " << a << ":" << b << std::endl;
    return 0;
}

      
int main(void)
{
    OEThreadPool::ThreadPoolConfig threadPoolConfig;
    threadPoolConfig.nMaxThreadsNum = 100;
    threadPoolConfig.nMinThreadsNum = 5;
    threadPoolConfig.dbTaskAddThreadRate = 3;
    threadPoolConfig.dbTaskSubThreadRate = 0.5;
    clock_t start = clock();
    {

        std::shared_ptr<OEThreadPool> threadPool(new OEThreadPool);
        threadPool->init(threadPoolConfig);

        int i = 0;
        while (true)
        {
            
            //std::shared_ptr<OEFunctionTask> request(new OEFunctionTask(vFunction));

            //threadPool->addTask(request);


            std::shared_ptr<OEFunctionTask> request2(new OEFunctionTask);
            request2->asynBind(hello, i++, std::string("http://blog.csdn.net/csnd_ayo/article/details/72457190"));

            threadPool->addTask(request2);

            //            if (request->getID() == 101000) {
            //				break;
            //            }
        }

        threadPool->release();
    }
    clock_t finish = clock();
    std::cout << "duration:" << finish - start << "ms" << std::endl;
    getchar();
    return 0;
}

