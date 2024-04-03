package com.ssafy.petpal.aop;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.reflect.MethodSignature;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class ExecutionTimeLoggingAspect {

    private static final Logger LOGGER = LoggerFactory.getLogger(ExecutionTimeLoggingAspect.class);

    @Around("execution(* com.ssafy.petpal..controller.*Controller.*(..))")
    public Object logExecutionTime(ProceedingJoinPoint joinPoint) throws Throwable {
        long start = System.nanoTime();
        Object result = joinPoint.proceed(); // 메서드 실행
        long executionTime = System.nanoTime() - start;

        // 나노세컨드를 밀리세컨드로 변환
        double executionTimeInMs = executionTime / 1_000_000.0;

        MethodSignature signature = (MethodSignature) joinPoint.getSignature();
        String methodName = signature.getMethod().getName();
        String className = joinPoint.getTarget().getClass().getSimpleName();

        // 실행 시간을 밀리세컨드 단위로 로그에 기록
        LOGGER.info("{}#{} executed in {} ms", className, methodName, executionTimeInMs);

        return result;
    }
}
