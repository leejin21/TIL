# 8.1 useState

가장 기본적인 Hook. 함수형 컴포넌트에서도 state와 setState를 쓸 수 있게 해 줌.

useState는 여러 개 사용할 수 있음.

-   참고

    [3장 컴포넌트](https://www.notion.so/3-f7b07ea749364e359dfc39037f8b17e5)

# 8.2 useEffect

리액트 컴포넌트가 렌더링될 때마다 특정 작업을 수행하도록 설정할 수 있는 Hook.

클래스형 컴포넌트의 라이프사이클 메서드 **componentDidMount**(마운트할 때 가장 마지막으로 호출되는 lc 메서드)와 **componentDidUpdate**(업데이트할 때 가장 마지막으로 호출되는 lc 메서드)를 합친 형태.

-   예제 코드(Info.js)

    ```jsx
    import React, { useEffect, useState } from "react";

    const Info = () => {
        const [name, setName] = useState("");
        const [nickName, setNickname] = useState("");
        useEffect(() => {
            // 2nd param에 아무것도 안 넣음: 렌더링을 할 때마다 실행됨
            console.log("렌더링이 완료되었습니다.");
            console.log({
                name,
                nickName,
            });
        });

        const onChange = (e) => {
            setName(e.target.value);
        };

        const onChangeNickname = (e) => {
            setNickname(e.target.value);
        };

        return (
            <div>
                <input
                    onChange={onChange}
                    placeholder="이름"
                    value={name}
                ></input>
                <input
                    onChange={onChangeNickname}
                    placeholder="닉네임"
                    value={nickName}
                ></input>
                <div>이름: {name}</div>
                <div>닉네임: {nickName}</div>
            </div>
        );
    };

    export default Info;
    ```

> useEffect는 렌더링 직후마다 실행됨 BUT 2nd param에 따라 실행될 지 말 지 결정됨.

## 마운트될 때만 useEffect를 실행하고 싶을 때

두번째 param에 비어 있는 배열 넣어주기

```jsx
useEffect(() => {
    // 2nd param에 빈 배열 넣기:
    console.log("마운트될 때만 실행됨");
}, []);
```

## 특정 값이 업데이트될 때만 실행하고 싶을 때

두번째 param에 [특정 값을 가리키는 변수명] 넣어주기. 이때 props, state 모두 가능!

```jsx
useEffect(() => {
    // 2nd param에 그 특정 값 넣어주기
    console.log(name);
}, [name]);
```

## 뒷정리하기

cleanup 함수 반환 ⇒ 컴포넌트가 **언마운트되기 전이나 업데이트되기 직전**에 어떠한 작업을 수행하고 싶을 때

-   예제 코드

# 8.3 useReducer

useState보다 **더 다양한 컴포넌트 상황에 따라 다양한 상태를 다른 값으로 업데이트해 주고 싶을 때** 쓰는 Hook.

## Reducer란?

```jsx
function reducer (state, action){
	// 불변성을 지키면서 업데이트한 새로운 상태를 반환
	return {...};
}
```

현재 상태, 그리고 업데이트를 위해 필요한 정보를 담은 액션(action)값을 전달받아 새로운 상태를 반환하는 함수. 리듀서 함수를 쓸 때는 **immutability(불변성) 원칙**을 지켜야 함.

17장에서 다룰 redux와는 달리, action 객체에 type 필드가 꼭 있어야 할 필요는 없음. 심지어 action도 객체일 필요는 없음.

## 카운터 구현하기

-   예제 코드(Info.js)

    ```jsx
    function reducer(prev, action) {
        switch (action.type) {
            case "PLUS":
                return { value: prev.value + 1 };
            case "MINUS":
                return { value: prev.value - 1 };
            default:
                return prev;
        }
    }

    const Counter = () => {
        const [state, dispatch] = useReducer(reducer, { value: 0 });

        return (
            <div>
                <p>
                    현재 카운터 값은 <b>{state.value}</b>입니다.
                </p>
                <button
                    onClick={() => {
                        dispatch({ type: "PLUS" });
                    }}
                >
                    +
                </button>
                <button
                    onClick={() => {
                        dispatch({ type: "MINUS" });
                    }}
                >
                    -
                </button>
            </div>
        );
    };
    ```

장점: component update logic을 바깥으로 빼낼 수 있다는 것

## 인풋 상태 관리하기

useReducer 사용해 Info 컴포넌트에서 인풋 상태를 관리해 보자.

-   예제 코드(Info.js)

    ```jsx
    const Info = () => {
        const [state, dispatch] = useReducer(reducer, {
            name: "",
            nickName: "",
        });

        const onChange = (e) => {
            console.log(e.target.name, e.target.value);
            dispatch(e.target);
        };

        return (
            <div>
                <input
                    name={"name"}
                    value={state.name}
                    onChange={onChange}
                ></input>
                <input
                    name={"nickName"}
                    value={state.nickName}
                    onChange={onChange}
                ></input>
                <div>이름: {state.name}</div>
                <div>닉네임: {state.nickName}</div>
            </div>
        );
    };
    ```

**e란?**
syntheticBaseEvent. 리액트에서 이벤트가 발생할 시, 이벤트 핸들러가 전달하는 인스턴스.
native event와 동일한 인터페이스를 가지고 있음(stopPropagation, preventDefault 포함).
즉, S급 짝퉁.

-   native event가 필요할 때를 위해 `event.nativeEvent.`stopImmediatePropagation()과 같이 쓸 수 있게 해 둠.
    [참고-리액트의 이벤트 핸들러 관련 글](https://medium.com/tapjoykorea/리액트-react-의-이벤트-핸들러-event-handler-syntheticevent-nativeevent-3a0da35e9e3f)

# 8.4 useMemo

함수형 컴포넌트 내부에서 발생하는 연산의 최적화를 위한 Hook.

-   예제 코드(Average.js)

    ```jsx
    const getAvg = (list) => {
        console.log("평균값 계산 중...");
        if (list.length === 0) return 0;
        const tot = list.reduce((a, b) => a + b);
        return tot / list.length;
    };

    const Average = () => {
        const [list, setList] = useState([]);
        const [num, setNum] = useState("");
        // string으로 num 받음
        const onChange = (e) => {
            setNum(e.target.value);
        };
        const onInsert = () => {
            if (num === "") {
                return;
            }
            const nextList = list.concat([parseInt(num)]);
            setList(nextList);
            // num은 string
            setNum("");
        };
        const avg = useMemo(() => getAvg(list), [list]);
        // 2nd param으로 dependency list가 들어옴. list 값이 바뀌어야 getAvg 호출하는 방식
        return (
            <div>
                <input value={num} onChange={onChange}></input>
                <button onClick={onInsert}>추가</button>
                <ul>
                    {list.map((v, i) => (
                        <li key={i}>{v}</li>
                    ))}
                </ul>
                <div>평균: {avg}</div>
            </div>
        );
    };
    ```

# 8.5 useCallback

위 GetAverage 컴포넌트에서 onChange랑 onInsert 함수는 컴포넌트가 리렌더링될 때마다 새로 생성됨. 컴포넌트의 리렌더링이 너무 자주 발생하면 이 부분을 useCallback과 같은 hooks로 최적화해 주는 게 좋음.

-   예제 코드(Average.js)

    ```jsx
    const Average = () => {
        const [list, setList] = useState([]);
        const [num, setNum] = useState("");
        // string으로 num 받음
        const onChange = useCallback((e) => {
            setNum(e.target.value);
        }, []);
        // 2nd param으로 빈 배열 건네주면서 컴포넌트 마운트할 때만 해당 함수 생성

        const onInsert = useCallback(() => {
            if (num === "") {
                return;
            }
            const nextList = list.concat([parseInt(num)]);
            setList(nextList);
            // num은 string
            setNum("");
        }, [num, list]);
        // 2nd param으로 [num, list] 건네주면서 num, list 값이 바뀔 때만 해당 함수 생성

        const avg = useMemo(() => getAvg(list), [list]);
        return (
            <div>
                <input value={num} onChange={onChange}></input>
                <button onClick={onInsert}>추가</button>
                <ul>
                    {list.map((v, i) => (
                        <li key={i}>{v}</li>
                    ))}
                </ul>
                <div>평균: {avg}</div>
            </div>
        );
    };
    ```

## useMemo vs useCallback

**useMemo**는 숫자, 객체, 문자열과 같은 일반 값을 재사용할 때 적합.

**useCallback**은 함수를 재사용하기에 적합.

-   예제 코드(Average.js)

    ```jsx
    // 다음 두 코드는 완전히 똑같은 코드임.
    useCallback(() => {
        console.log("hello world");
    }, []);

    useMemo(() => {
        const fn = () => {
            console.log("hello world!");
        };
        return fn;
    }, []);
    ```

# 8.6 useRef

함수형 컴포넌트에서 ref를 쉽게 사용할 수 있도록 해 줌.

-   예제 코드(Average.js)

    ```jsx
    // * 8.6 useRef 예제 코드
    const Average = () => {
        const [list, setList] = useState([]);
        const [num, setNum] = useState("");
        const inputEl = useRef(null);
        // string으로 num 받음
        const onChange = useCallback((e) => {
            setNum(e.target.value);
        }, []);
        // 2nd param으로 빈 배열 건네주면서 컴포넌트 마운트할 때만 해당 함수 생성

        const onInsert = useCallback(() => {
            inputEl.current.focus();
            if (num === "") {
                return;
            }
            const nextList = list.concat([parseInt(num)]);
            setList(nextList);
            // num은 string
            setNum("");
        }, [num, list]);
        // 2nd param으로 [num, list] 건네주면서 num, list 값이 바뀔 때만 해당 함수 생성

        const avg = useMemo(() => getAvg(list), [list]);
        return (
            <div>
                <input value={num} onChange={onChange} ref={inputEl}></input>
                <button onClick={onInsert}>추가</button>
                <ul>
                    {list.map((v, i) => (
                        <li key={i}>{v}</li>
                    ))}
                </ul>
                <div>평균: {avg}</div>
            </div>
        );
    };
    ```

## 로컬 변수 사용하기

로컬 변수란, 렌더링과 상관 없이 바뀔 수 있는 값을 의미. useRef는 이런 로컬 변수를 리렌더링 없이 값을 관리할 수 있음.

-   예제 코드(RefSample.js)

    ```jsx
    import React, { useRef } from "react";

    const RefSample = () => {
        const id = useRef(1);
        const setId = (n) => {
            id.current = n;
        };
        const printid = () => {
            console.log(id.current);
        };
        return <div>refsample</div>;
    };

    export default RefSample;
    ```

이걸 언제 사용할까?

# 8.7 커스텀 Hooks 만들기

기존의 hooks를 이용해서 커스텀 hooks 만들기

-   예제 코드(useInputs.js)

    ```jsx
    import { useReducer } from "react";

    function reducer(state, action) {
        return {
            ...state,
            [action.name]: action.value,
        };
    }

    export default function useInputs(initialForm) {
        const [state, dispatch] = useReducer(reducer, initialForm);
        const onChange = (e) => {
            dispatch(e.target);
        };
        return [state, onChange];
    }
    ```

-   예제 코드(Info.js)

    ```jsx
    // * 8.7 커스텀 Hooks 만들기

    const Info = () => {
        const [state, onChange] = useInputs({ name: "", nickname: "" });
        const { name, nickname } = state;
        return (
            <div>
                <input name="name" onChange={onChange} value={name}></input>
                <input
                    name="nickname"
                    onChange={onChange}
                    value={nickname}
                ></input>
                <div>
                    이름: {name}
                    닉네임: {nickname}
                </div>
            </div>
        );
    };
    ```

# 8.8 다른 Hooks

—생략—

# 8.9 정리

앞으로도 클래스형 컴포넌트는 없어지지 않을 거임.

단, 함수형 컴포넌트를 더 권장하니 새로 만드는 프로젝트의 경우 함수형 컴포넌트를 최우선으로 생각하되, 꼭 필요한 경우에만 클래스형 컴포넌트 이용하기.
